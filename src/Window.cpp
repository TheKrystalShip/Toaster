#include "Errors.h"
#include "Window.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <string>

namespace Toaster
{
    Window::Window() : _vsync(false)
    {
    }

    Window::~Window()
    {
    }

    int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags)
    {
        Uint32 flags = SDL_WINDOW_OPENGL;

        if (currentFlags & WindowFlags::INVISIBLE)
            flags |= SDL_WINDOW_HIDDEN;

        if (currentFlags & WindowFlags::FULLSCREEN)
            flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

        if (currentFlags & WindowFlags::BORDERLESS)
            flags |= SDL_WINDOW_BORDERLESS;

        _sdlWindow = SDL_CreateWindow(
            windowName.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            screenWidth,
            screenHeight,
            flags);

        _width = screenWidth;
        _height = screenHeight;

        if (_sdlWindow == nullptr)
            fatalError("SDL_CreateWindow returned nullptr");

        SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);

        if (glContext == nullptr)
            fatalError("SDL_GL_CreateContext returned nullptr");

        GLenum error = glewInit();

        if (error != GLEW_OK)
            fatalError("glewInit is not GLEW_OK");

        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

        std::printf("***   OpenGL Version: %s   ***\n", glGetString(GL_VERSION));

        // V-SYNC = 1: on, 0: off
        SDL_GL_SetSwapInterval(0);

        // Enable alpha blending
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        return 0;
    }

    void Window::swapBuffer()
    {
        SDL_GL_SwapWindow(_sdlWindow);
    }
}
