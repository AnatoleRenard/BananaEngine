#include "Window.hpp"

namespace banana
{
    void Window::resize(int& width, int& height)
    {
        SDL_GetWindowSize(m_Window, &m_Width, &m_Height);
        width = m_Width;
        height = m_Height;
    }

    //utility functions
    int Window::getWidth() const
    {
        return m_Width;
    }

    int Window::getHeight() const
    {
        return m_Height;
    }

    bool Window::getFullscreen() const
    {
        return checkFlag(getWindowFlags(), toSDLWindowFlag(BANANA_WINDOW_FULLSCREEN));
    }

    void Window::setFullscreen(bool s)
    {
        SDL_SetWindowFullscreen(m_Window, s ? (toSDLWindowFlag(BANANA_WINDOW_FULLSCREEN)) : 0);
    }

    bool Window::getBorderless() const
    {
        return checkFlag(getWindowFlags(), toSDLWindowFlag(BANANA_WINDOW_BORDERLESS));
    }

    void Window::setBorderless(bool s)
    {
        SDL_SetWindowBordered(m_Window, s ? SDL_FALSE : SDL_TRUE);
    }

    bool Window::getResizable() const
    {
        return checkFlag(getWindowFlags(), toSDLWindowFlag(BANANA_WINDOW_RESIZABLE));
    }

    void Window::setResizable(bool s)
    {
        SDL_SetWindowResizable(m_Window, s ? SDL_TRUE : SDL_FALSE);
    }

    uint32_t Window::getWindowFlags() const
    {
        return SDL_GetWindowFlags(m_Window);
    }
}