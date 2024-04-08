#include "Toaster.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>

int Toaster::init()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    return 0;
}
