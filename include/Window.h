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

        int create(std::string windowName, int width, int height, unsigned int currentFlags = WindowFlags::DEFAULT);

        void swapBuffer();

        int getWidth() { return _width; }
        int getHeight() { return _height; }

        void setVsync(const bool val) { _vsync = val; }
        bool getVsync() const { return _vsync; }

    private:
        int _width;
        int _height;
        SDL_Window *_sdlWindow;
        bool _vsync;
    };
}
