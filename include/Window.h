#pragma once

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <string>

namespace Toaster
{
    enum WindowFlags
    {
        DEFAULT = 0x0,
        INVISIBLE = 0x1,
        FULLSCREEN = 0x2,
        BORDERLESS = 0x4
    };

    class Window
    {
    public:
        Window();
        ~Window();

        int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags = WindowFlags::DEFAULT);

        void swapBuffer();

        int getScreenWidth() { return _screenWidth; }
        int getScreenHeight() { return _screenHeight; }

        void setVsync(const bool val) { _vsync = val; }
        bool getVsync() const { return _vsync; }

    private:
        int _screenWidth;
        int _screenHeight;
        SDL_Window *_sdlWindow;
        bool _vsync;
    };
}
