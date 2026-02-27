#pragma once

#include "GameController.hpp"

namespace banana
{
    class Input
    {
        public:
            static void init();
            static void close();
            

            static void update();
            
            //get events
            static KeyStates getKey(Keys key);
            
            static MouseButtonStates getMouseButton(MouseButtons button);
            static MouseClickStates getMouseClick(MouseButtons button);
            static void getMousePos(int &x, int &y);
            static int getMouseX();
            static int getMouseY();
            static void getMouseRelPos(int &dx, int &dy);
            static int getMouseRelX();
            static int getMouseRelY();
            
            static WindowEvents getWindowEvent();
            
            static bool getQuit();

            static Controller getNextController(); //returns -1 if no next controller
            static Controller getNextDisconectedController(); //returns -1 if no next
            static bool getNewControllerConnected();
            static bool getControllerDisconnected();
            static bool getControllerExists(Controller controller);

            static GameControllerButtonStates getControllerButton(Controller controller, GameControllerButtons button);
            static GameControllerBrand getControllerBrand(Controller controller);
            static float getControllerAxis(Controller controller, GameControllerAxis axis);
            static bool getControllerConnected(Controller controller);
        
        private:
            //keyboard
            static std::array<KeyStates, static_cast<id_t>(Keys::COUNT)> m_KeyStates;

            //window event status
            static WindowEvents m_WindowEvent;

            //mouse input
            static std::array<MouseButtonStates, static_cast<id_t>(MouseButtons::COUNT)> m_MouseButtonStates;
            static std::array<MouseClickStates, static_cast<id_t>(MouseButtons::COUNT)> m_MouseClickState;
            static int m_MouseX;
            static int m_MouseY;
            static int m_MouseRelX; //relative x to last frame
            static int m_MouseRelY; //relative y to last frame

            //game controllers
            static std::unordered_map<Controller, std::unique_ptr<GameController>> m_Controllers;
            static std::vector<Controller> m_NextController; // next controller to give to user
            static std::vector<Controller> m_ControllerLeft; //controllers that left

            //SDL_Quit triggered
            static bool m_Quit;

            //returns index for map implementation
            static id_t fromSDL(SDL_Scancode code); //keyboard
            static id_t fromSDL(uint8_t code); //mouse

            //handle controller events
            static float filter(int value);
    };
}