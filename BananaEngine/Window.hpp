#pragma once

#include "Core.hpp"

namespace banana
{
    //window flags
    const uint32_t BANANA_WINDOW_FULLSCREEN          = 0x00000001;    /**< window is in fullscreen mode */
    const uint32_t BANANA_WINDOW_OPENGL              = 0x00000002;    /**< window usable with OpenGL context */
    const uint32_t BANANA_WINDOW_SHOWN               = 0x00000004;    /**< window is shown */
    const uint32_t BANANA_WINDOW_HIDDEN              = 0x00000008;    /**< window is neither mapped onto the desktop nor shown in the taskbar/dock/window list; SDL_ShowWindow() is required for it to become visible */
    const uint32_t BANANA_WINDOW_BORDERLESS          = 0x00000010;    /**< no window decoration */
    const uint32_t BANANA_WINDOW_RESIZABLE           = 0x00000020;    /**< window can be resized */
    const uint32_t BANANA_WINDOW_MINIMIZED           = 0x00000040;    /**< window is minimized */
    const uint32_t BANANA_WINDOW_MAXIMIZED           = 0x00000080;    /**< window is maximized */
    const uint32_t BANANA_WINDOW_MOUSE_GRABBED       = 0x00000100;    /**< window has grabbed mouse input */
    const uint32_t BANANA_WINDOW_INPUT_FOCUS         = 0x00000200;    /**< window has input focus */
    const uint32_t BANANA_WINDOW_MOUSE_FOCUS         = 0x00000400;    /**< window has mouse focus */
    const uint32_t BANANA_WINDOW_MOUSE_CAPTURE       = 0x00004000;    /**< window has mouse captured (unrelated to MOUSE_GRABBED) */
    const uint32_t BANANA_WINDOW_ALWAYS_ON_TOP       = 0x00010000;    /**< window should always be above others */
    const uint32_t BANANA_WINDOW_UTILITY             = 0x00020000;    /**< window should be treated as a utility window, not showing in the task bar and window list */
    const uint32_t BANANA_WINDOW_TOOLTIP             = 0x00040000;    /**< window should be treated as a tooltip and does not get mouse or keyboard focus, requires a parent window */
    const uint32_t BANANA_WINDOW_POPUP_MENU          = 0x00080000;    /**< window should be treated as a popup menu, requires a parent window */
    const uint32_t BANANA_WINDOW_KEYBOARD_GRABBED    = 0x00100000;    /**< window has grabbed keyboard input */
    const uint32_t BANANA_WINDOW_VULKAN              = 0x10000000;    /**< window usable for Vulkan surface */
    const uint32_t BANANA_WINDOW_METAL               = 0x20000000;    /**< window usable for Metal view */

    class Window
    {
        public:
            virtual ~Window() = default;

            virtual void update() const = 0;

            void resize(int& width, int& height);

            //utility functions
            int getWidth() const;
            int getHeight() const;

            bool getFullscreen() const;
            void setFullscreen(bool s);

            bool getBorderless() const;
            void setBorderless(bool s);

            bool getResizable() const;
            void setResizable(bool s);

        protected:
            SDL_Window* m_Window;

            int m_Width;
            int m_Height;

            uint32_t getWindowFlags() const;
    };


    inline uint32_t toSDLWindowFlag(uint32_t flag)
    {
        uint32_t sdlFlag = 0;
        if(checkFlag(flag, BANANA_WINDOW_FULLSCREEN))
            sdlFlag |= SDL_WINDOW_FULLSCREEN_DESKTOP;
        
        if(checkFlag(flag, BANANA_WINDOW_OPENGL))
            sdlFlag |= SDL_WINDOW_OPENGL;

        if(checkFlag(flag, BANANA_WINDOW_HIDDEN))
            sdlFlag |= SDL_WINDOW_HIDDEN;
        
        if(checkFlag(flag, BANANA_WINDOW_BORDERLESS))
            sdlFlag |= SDL_WINDOW_BORDERLESS;
        
        if(checkFlag(flag, BANANA_WINDOW_RESIZABLE))
            sdlFlag |= SDL_WINDOW_RESIZABLE;
        
        if(checkFlag(flag, BANANA_WINDOW_MINIMIZED))
            sdlFlag |= SDL_WINDOW_MINIMIZED;
        
        if(checkFlag(flag, BANANA_WINDOW_MAXIMIZED))
            sdlFlag |= SDL_WINDOW_MAXIMIZED;
        
        if(checkFlag(flag, BANANA_WINDOW_MOUSE_GRABBED))
            sdlFlag |= SDL_WINDOW_MOUSE_GRABBED;
        
        if(checkFlag(flag, BANANA_WINDOW_INPUT_FOCUS))
            sdlFlag |= SDL_WINDOW_INPUT_FOCUS;
        
        if(checkFlag(flag, BANANA_WINDOW_MOUSE_FOCUS))
            sdlFlag |= SDL_WINDOW_MOUSE_FOCUS;
        
        if(checkFlag(flag, BANANA_WINDOW_MOUSE_CAPTURE))
            sdlFlag |= SDL_WINDOW_MOUSE_CAPTURE;
        
        if(checkFlag(flag, BANANA_WINDOW_ALWAYS_ON_TOP))
            sdlFlag |= SDL_WINDOW_ALWAYS_ON_TOP;
        
        if(checkFlag(flag, BANANA_WINDOW_UTILITY))
            sdlFlag |= SDL_WINDOW_UTILITY;
        
        if(checkFlag(flag, BANANA_WINDOW_TOOLTIP))
            sdlFlag |= SDL_WINDOW_TOOLTIP;
        
        if(checkFlag(flag, BANANA_WINDOW_POPUP_MENU))
            sdlFlag |= SDL_WINDOW_POPUP_MENU;
        
        if(checkFlag(flag, BANANA_WINDOW_VULKAN))
            sdlFlag |= SDL_WINDOW_VULKAN;
        
        if(checkFlag(flag, BANANA_WINDOW_METAL))
            sdlFlag |= SDL_WINDOW_METAL;
        
        return sdlFlag;
    }
}