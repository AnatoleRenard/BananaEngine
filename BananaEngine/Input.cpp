#include "Input.hpp"

namespace banana
{
    //declare static variables
    //keyboard
    std::array<KeyStates, static_cast<id_t>(Keys::COUNT)> Input::m_KeyStates;

    //window event status
    WindowEvents Input::m_WindowEvent;

    //mouse input
    std::array<MouseButtonStates, static_cast<id_t>(MouseButtons::COUNT)> Input::m_MouseButtonStates;
    std::array<MouseClickStates, static_cast<id_t>(MouseButtons::COUNT)> Input::m_MouseClickState;
    int Input::m_MouseX;
    int Input::m_MouseY;
    int Input::m_MouseRelX; //relative x to last frame
    int Input::m_MouseRelY; //relative y to last frame

    //game controllers
    std::unordered_map<id_t, std::unique_ptr<GameController>> Input::m_Controllers;
    std::vector<Controller> Input::m_NextController;
    std::vector<Controller> Input::m_ControllerLeft;

    //SDL_Quit triggered
    bool Input::m_Quit;

    void Input::init()
    {
        m_Quit = false;
        
        for(id_t i = 0; i < static_cast<id_t>(Keys::COUNT); i++)
        {
            m_KeyStates[i] = KeyStates::RELEASED;
        }

        for(id_t i = 0; i < static_cast<id_t>(MouseButtons::COUNT); i++)
        {
            m_MouseButtonStates[i] = MouseButtonStates::RELEASED;
        }

        for(id_t i = 0; i < static_cast<id_t>(MouseButtons::COUNT); i++)
        {
            m_MouseClickState[i] = MouseClickStates::NONE;
        }

        //internally update to add controllers etc.
        update();

        BANANA_INFO("Initiated input system!");
    }

    void Input::close()
    {
        m_Controllers.clear();
        BANANA_INFO("Closed input system!");
    }

    void Input::update()
    {
        m_WindowEvent = WindowEvents::NONE;
        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {

                //quit
                case SDL_QUIT:
                    m_Quit = true;
                    break;
                
                //keyboard
                case SDL_KEYDOWN:
                    m_KeyStates[fromSDL(e.key.keysym.scancode)] = KeyStates::PRESSED;
                    break;
                
                case SDL_KEYUP:
                    m_KeyStates[fromSDL(e.key.keysym.scancode)] = KeyStates::RELEASED;
                    break;
                
                //window event
                case SDL_WINDOWEVENT:
                    if(e.window.event == SDL_WINDOWEVENT_RESIZED)
                    {
                        m_WindowEvent = WindowEvents::RESIZED;
                    }
                    break;
                
                //mouse events
                case SDL_MOUSEBUTTONDOWN:
                    m_MouseButtonStates[fromSDL(e.button.button)] = MouseButtonStates::PRESSED;

                    if(e.button.clicks == 1)
                        m_MouseClickState[fromSDL(e.button.button)] = MouseClickStates::SINGLE;
                    else if(e.button.clicks == 2)
                        m_MouseClickState[fromSDL(e.button.button)] = MouseClickStates::DOUBLE;
                    break;
                
                case SDL_MOUSEBUTTONUP:
                    m_MouseButtonStates[fromSDL(e.button.button)] = MouseButtonStates::RELEASED;
                    m_MouseClickState[fromSDL(e.button.button)] = MouseClickStates::NONE;
                    break;

                case SDL_MOUSEMOTION:
                    m_MouseX = e.motion.x;
                    m_MouseY = e.motion.y;
                    m_MouseRelX = e.motion.xrel;
                    m_MouseRelY = e.motion.yrel;
                    break;
                
                //game controller connection
                case SDL_CONTROLLERDEVICEADDED:
                    {
                        auto controller = std::make_unique<GameController>(e.cdevice.which);
                        
                        SDL_Joystick* joy = SDL_GameControllerGetJoystick(controller->getHandle());

                        SDL_JoystickID instance = SDL_JoystickInstanceID(joy);

                        m_Controllers[instance] = std::move(controller);
                        
                        m_NextController.push_back(instance);
                    }
                    break;
                
                case SDL_CONTROLLERDEVICEREMOVED:
                    m_ControllerLeft.push_back(e.cdevice.which);
                    m_Controllers[e.cdevice.which]->disconect();
                    m_Controllers.erase(e.cdevice.which);
                    break;
                
                //game controller input
                case SDL_CONTROLLERBUTTONDOWN:
                    {
                    auto iterator = m_Controllers.find(e.cdevice.which);

                    if(iterator != m_Controllers.end())
                        iterator->second->updateButton(static_cast<SDL_GameControllerButton>(e.cbutton.button), true);
                    }
                    break;
                
                case SDL_CONTROLLERBUTTONUP:
                    {
                    auto iterator = m_Controllers.find(e.cdevice.which);

                    if(iterator != m_Controllers.end())
                        iterator->second->updateButton(static_cast<SDL_GameControllerButton>(e.cbutton.button), false);
                    }
                    break;
                
                case SDL_CONTROLLERAXISMOTION:
                    {
                    auto iterator = m_Controllers.find(e.cdevice.which);

                    if(iterator != m_Controllers.end())
                        iterator->second->updatAxis(static_cast<SDL_GameControllerAxis>(e.caxis.axis), filter(e.caxis.value));
                    }
                    break;
            }
        }
    }

    KeyStates Input::getKey(Keys key)
    {
        return m_KeyStates[static_cast<id_t>(key)];
    }

    MouseButtonStates Input::getMouseButton(MouseButtons button)
    {
        return m_MouseButtonStates[static_cast<id_t>(button)];
    }

    MouseClickStates Input::getMouseClick(MouseButtons button)
    {
        return m_MouseClickState[static_cast<id_t>(button)];
    }

    void Input::getMousePos(int& x, int& y)
    {
        x = m_MouseX;
        y = m_MouseY;
    }

    int Input::getMouseX()
    {
        return m_MouseX;
    }
        
    int Input::getMouseY()
    {
        return m_MouseY;
    }

    void Input::getMouseRelPos(int& x, int& y)
    {
        x = m_MouseRelX;
        y = m_MouseRelY;
    }

    int Input::getMouseRelX()
    {
        return m_MouseRelX;
    }
        
    int Input::getMouseRelY()
    {
        return m_MouseRelY;
    }

    WindowEvents Input::getWindowEvent()
    {
        return m_WindowEvent;
    }

    Controller Input::getNextController()
    {
        if(!getNewControllerConnected()) return -1;
        Controller c = m_NextController[0];
        m_NextController.erase(m_NextController.begin());
        return c;
    }

    Controller Input::getNextDisconectedController()
    {
        if(!getControllerDisconnected()) return -1;
        Controller c = m_ControllerLeft[0];
        m_ControllerLeft.erase(m_ControllerLeft.begin());

        //erase controller as is now known by user that it is removed
        m_Controllers.erase(c);
        return c;
    }

    bool Input::getNewControllerConnected()
    {
        return m_NextController.size() > 0;
    }

    bool Input::getControllerDisconnected()
    {
        return m_ControllerLeft.size() > 0;
    }

    bool Input::getControllerExists(Controller controller)
    {
        auto iterator = m_Controllers.find(controller);

        if(iterator != m_Controllers.end())
            return true;
        return false;
    }

    bool Input::getQuit()
    {
        return m_Quit;
    }

    GameControllerButtonStates Input::getControllerButton(Controller controller, GameControllerButtons button)
    {
        auto iterator = m_Controllers.find(controller);

        if(iterator != m_Controllers.end())
            return iterator->second->getButton(button);
        
        return GameControllerButtonStates::RELEASED;
    }

    GameControllerBrand Input::getControllerBrand(Controller controller)
    {
        auto iterator = m_Controllers.find(controller);

        if(iterator != m_Controllers.end())
            return iterator->second->getBrand();
        
        return GameControllerBrand::UNKNOWN;
    }

    float Input::getControllerAxis(Controller controller, GameControllerAxis axis)
    {
        auto iterator = m_Controllers.find(controller);

        if(iterator != m_Controllers.end())
            return iterator->second->getAxis(axis);

        return 0.0f;
    }

    bool Input::getControllerConnected(Controller controller)
    {
        auto iterator = m_Controllers.find(controller);

        if(iterator != m_Controllers.end())
            return iterator->second->getConnection();

        return false;
    }

    id_t Input::fromSDL(SDL_Scancode code)
    {
        auto iterator = KEYMAP.find(code);

        if(iterator != KEYMAP.end())
            return static_cast<id_t>(iterator->second);
        return static_cast<id_t>(Keys::UNKNOWN);
    }

    id_t Input::fromSDL(uint8_t code)
    {
        auto iterator = MOUSEBUTTONMAP.find(code);

        if(iterator != MOUSEBUTTONMAP.end())
            return static_cast<id_t>(iterator->second);
        return static_cast<id_t>(MouseButtons::UNKNOWN);
    }

    float Input::filter(int value)
    {
        //if is in dead zone
        value = (value < GAMECONTROLLER_DEAD_ZONE && value > -GAMECONTROLLER_DEAD_ZONE) ? 0 : value;
        
        //if is outside allowed zone
        value = (value > GAMECONTROLLER_MAX_VAL) ? GAMECONTROLLER_MAX_VAL : (value < -GAMECONTROLLER_MAX_VAL) ? -GAMECONTROLLER_MAX_VAL : value;

        //return as float
        return value / float(GAMECONTROLLER_MAX_VAL);
    }
}