#pragma once
#include "Window.hpp"

namespace banana
{
    //Define all keyboard inputs
    enum class KeyStates : uint8_t
    {
        RELEASED,
        PRESSED
    };

    enum class Keys : uint8_t
    {
        // Letters
        A, B, C, D, E, F, G, H, I, J, K, L, M,
        N, O, P, Q, R, S, T, U, V, W, X, Y, Z,

        // Numbers
        Num0, Num1, Num2, Num3, Num4,
        Num5, Num6, Num7, Num8, Num9,

        // Control
        Enter, Escape, Backspace, Tab, Space,

        // Modifiers
        LeftShift, RightShift,
        LeftCtrl, RightCtrl,
        LeftAlt, RightAlt,
        LeftSuper, RightSuper,

        // Arrows
        Left, Right, Up, Down,

        // Navigation
        Insert, Delete,
        Home, End,
        PageUp, PageDown,

        // Function keys
        F1, F2, F3, F4, F5, F6,
        F7, F8, F9, F10, F11, F12,

        // Unknown
        UNKNOWN,

        COUNT
    };


    //sdl to my implementation
    const std::unordered_map<SDL_Scancode, Keys> KEYMAP =
    {
        // Letters
        { SDL_SCANCODE_A, Keys::A },
        { SDL_SCANCODE_B, Keys::B },
        { SDL_SCANCODE_C, Keys::C },
        { SDL_SCANCODE_D, Keys::D },
        { SDL_SCANCODE_E, Keys::E },
        { SDL_SCANCODE_F, Keys::F },
        { SDL_SCANCODE_G, Keys::G },
        { SDL_SCANCODE_H, Keys::H },
        { SDL_SCANCODE_I, Keys::I },
        { SDL_SCANCODE_J, Keys::J },
        { SDL_SCANCODE_K, Keys::K },
        { SDL_SCANCODE_L, Keys::L },
        { SDL_SCANCODE_M, Keys::M },
        { SDL_SCANCODE_N, Keys::N },
        { SDL_SCANCODE_O, Keys::O },
        { SDL_SCANCODE_P, Keys::P },
        { SDL_SCANCODE_Q, Keys::Q },
        { SDL_SCANCODE_R, Keys::R },
        { SDL_SCANCODE_S, Keys::S },
        { SDL_SCANCODE_T, Keys::T },
        { SDL_SCANCODE_U, Keys::U },
        { SDL_SCANCODE_V, Keys::V },
        { SDL_SCANCODE_W, Keys::W },
        { SDL_SCANCODE_X, Keys::X },
        { SDL_SCANCODE_Y, Keys::Y },
        { SDL_SCANCODE_Z, Keys::Z },

        // Numbers
        { SDL_SCANCODE_0, Keys::Num0 },
        { SDL_SCANCODE_1, Keys::Num1 },
        { SDL_SCANCODE_2, Keys::Num2 },
        { SDL_SCANCODE_3, Keys::Num3 },
        { SDL_SCANCODE_4, Keys::Num4 },
        { SDL_SCANCODE_5, Keys::Num5 },
        { SDL_SCANCODE_6, Keys::Num6 },
        { SDL_SCANCODE_7, Keys::Num7 },
        { SDL_SCANCODE_8, Keys::Num8 },
        { SDL_SCANCODE_9, Keys::Num9 },

        // Control
        { SDL_SCANCODE_RETURN,    Keys::Enter },
        { SDL_SCANCODE_ESCAPE,    Keys::Escape },
        { SDL_SCANCODE_BACKSPACE, Keys::Backspace },
        { SDL_SCANCODE_TAB,       Keys::Tab },
        { SDL_SCANCODE_SPACE,     Keys::Space },

        // Modifiers
        { SDL_SCANCODE_LSHIFT, Keys::LeftShift },
        { SDL_SCANCODE_RSHIFT, Keys::RightShift },
        { SDL_SCANCODE_LCTRL,  Keys::LeftCtrl },
        { SDL_SCANCODE_RCTRL,  Keys::RightCtrl },
        { SDL_SCANCODE_LALT,   Keys::LeftAlt },
        { SDL_SCANCODE_RALT,   Keys::RightAlt },
        { SDL_SCANCODE_LGUI,   Keys::LeftSuper },
        { SDL_SCANCODE_RGUI,   Keys::RightSuper },

        // Arrows
        { SDL_SCANCODE_LEFT,  Keys::Left },
        { SDL_SCANCODE_RIGHT, Keys::Right },
        { SDL_SCANCODE_UP,    Keys::Up },
        { SDL_SCANCODE_DOWN,  Keys::Down },

        // Navigation
        { SDL_SCANCODE_INSERT,   Keys::Insert },
        { SDL_SCANCODE_DELETE,   Keys::Delete },
        { SDL_SCANCODE_HOME,     Keys::Home },
        { SDL_SCANCODE_END,      Keys::End },
        { SDL_SCANCODE_PAGEUP,   Keys::PageUp },
        { SDL_SCANCODE_PAGEDOWN, Keys::PageDown },

        // Function keys
        { SDL_SCANCODE_F1,  Keys::F1 },
        { SDL_SCANCODE_F2,  Keys::F2 },
        { SDL_SCANCODE_F3,  Keys::F3 },
        { SDL_SCANCODE_F4,  Keys::F4 },
        { SDL_SCANCODE_F5,  Keys::F5 },
        { SDL_SCANCODE_F6,  Keys::F6 },
        { SDL_SCANCODE_F7,  Keys::F7 },
        { SDL_SCANCODE_F8,  Keys::F8 },
        { SDL_SCANCODE_F9,  Keys::F9 },
        { SDL_SCANCODE_F10, Keys::F10 },
        { SDL_SCANCODE_F11, Keys::F11 },
        { SDL_SCANCODE_F12, Keys::F12 },

        // Unkown
        { SDL_SCANCODE_UNKNOWN, Keys::UNKNOWN}
    };

    //window event inputs
    enum class WindowEvents : uint8_t
    {
        RESIZED,
        NONE
    };

    //mouse events
    enum class MouseButtonStates : uint8_t
    {
        RELEASED,
        PRESSED
    };

    enum class MouseButtons : uint8_t
    {
        ButtonL,
        ButtonM, //wheel click
        ButtonR,
        ButtonX1, //extra button 1
        ButtonX2, //extra button 2
        
        UNKNOWN,
        COUNT
    };

    enum class MouseClickStates : uint8_t
    {
        SINGLE,
        DOUBLE,
        NONE
    };

    const std::unordered_map<uint8_t, MouseButtons> MOUSEBUTTONMAP =
    {
        {SDL_BUTTON_LEFT, MouseButtons::ButtonL},
        {SDL_BUTTON_RIGHT, MouseButtons::ButtonR},
        {SDL_BUTTON_MIDDLE, MouseButtons::ButtonM},
        {SDL_BUTTON_X1, MouseButtons::ButtonX1},
        {SDL_BUTTON_X2, MouseButtons::ButtonX2}
    };

    //game controllers
    constexpr int GAMECONTROLLER_DEAD_ZONE = 10000;
    constexpr int GAMECONTROLLER_MAX_VAL   = 30000;
    
    using Controller = id_t;

    enum class GameControllerButtonStates : uint8_t
    {
        RELEASED,
        PRESSED
    };

    enum class GameControllerButtons : uint8_t
    {
               // Xbox/   PS  / Switch
        South, //  A  / Cross / B
        North, //  Y  /  Tri  / X
        West,  //  X  / Squar / Y
        East,  //  B  / Cirle / A

        Start,
        Select,

        //Shoudlers/Bumpers
        LeftBump,
        RightBump,

        //Dpad
        DUp,
        DDown,
        DLeft,
        DRight,

        //joystick
        LStick,
        RStick,

        //ps5 touchpad
        TouchPad,

        //misc
        MISC, // switch -> capture, ps5 -> microphone, xbox x -> share

        UNKNOWN,
        COUNT
    };

    enum class GameControllerAxis : uint8_t
    {
        //joysticks
        LeftX,
        LeftY,
        RightX,
        RightY,
        
        //triggers
        LeftT,
        RightT,

        UNKNOWN,
        COUNT
    };

    enum class GameControllerBrand : uint8_t
    {
        Xbox360,
        XboxOne,
        SwitchPro,
        SwitxhPair, //onyl support joycon if a pair
        Ps3,
        Ps4,
        Ps5,

        UNKNOWN,
        COUNT
    };

    const std::unordered_map<SDL_GameControllerButton, GameControllerButtons> GAMECONTROLLERBUTTOMMAP = 
    {
        {SDL_CONTROLLER_BUTTON_A, GameControllerButtons::South},
        {SDL_CONTROLLER_BUTTON_B, GameControllerButtons::East},
        {SDL_CONTROLLER_BUTTON_X, GameControllerButtons::West},
        {SDL_CONTROLLER_BUTTON_Y, GameControllerButtons::North},

        {SDL_CONTROLLER_BUTTON_START, GameControllerButtons::Start},
        {SDL_CONTROLLER_BUTTON_BACK, GameControllerButtons::Select},
        
        {SDL_CONTROLLER_BUTTON_LEFTSHOULDER, GameControllerButtons::LeftBump},
        {SDL_CONTROLLER_BUTTON_RIGHTSHOULDER, GameControllerButtons::RightBump},

        {SDL_CONTROLLER_BUTTON_DPAD_UP, GameControllerButtons::DUp},
        {SDL_CONTROLLER_BUTTON_DPAD_DOWN, GameControllerButtons::DDown},
        {SDL_CONTROLLER_BUTTON_DPAD_LEFT, GameControllerButtons::DLeft},
        {SDL_CONTROLLER_BUTTON_DPAD_RIGHT, GameControllerButtons::DRight},

        {SDL_CONTROLLER_BUTTON_LEFTSTICK, GameControllerButtons::LStick},
        {SDL_CONTROLLER_BUTTON_RIGHTSTICK, GameControllerButtons::RStick},

        {SDL_CONTROLLER_BUTTON_TOUCHPAD, GameControllerButtons::TouchPad},

        {SDL_CONTROLLER_BUTTON_MISC1, GameControllerButtons::MISC}
    };

    const std::unordered_map<SDL_GameControllerAxis, GameControllerAxis> GAMECONTROLLERAXISMAP =
    {
        {SDL_CONTROLLER_AXIS_LEFTX, GameControllerAxis::LeftX},
        {SDL_CONTROLLER_AXIS_LEFTY, GameControllerAxis::LeftY},
        {SDL_CONTROLLER_AXIS_RIGHTX, GameControllerAxis::RightX},
        {SDL_CONTROLLER_AXIS_RIGHTY, GameControllerAxis::RightY},

        {SDL_CONTROLLER_AXIS_TRIGGERLEFT, GameControllerAxis::LeftT},
        {SDL_CONTROLLER_AXIS_TRIGGERRIGHT, GameControllerAxis::RightT}
    };

    const std::unordered_map<SDL_GameControllerType, GameControllerBrand> GAMECONTROLLERBRANDMAP = 
    {
        {SDL_CONTROLLER_TYPE_XBOX360, GameControllerBrand::Xbox360},
        {SDL_CONTROLLER_TYPE_XBOXONE, GameControllerBrand::XboxOne},
        {SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_PRO, GameControllerBrand::SwitchPro},
        {SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_JOYCON_PAIR, GameControllerBrand::SwitxhPair},
        {SDL_CONTROLLER_TYPE_PS3, GameControllerBrand::Ps3},
        {SDL_CONTROLLER_TYPE_PS4, GameControllerBrand::Ps4},
        {SDL_CONTROLLER_TYPE_PS5, GameControllerBrand::Ps5},
        {SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_JOYCON_LEFT, GameControllerBrand::UNKNOWN},
        {SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_JOYCON_RIGHT, GameControllerBrand::UNKNOWN},
        {SDL_CONTROLLER_TYPE_UNKNOWN, GameControllerBrand::UNKNOWN}
    };
}