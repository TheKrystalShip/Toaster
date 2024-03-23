#include "Errors.h"

#include <SDL2/SDL.h>

#include <cstdlib>
#include <string>
#include <iostream>

namespace Toaster
{
    void fatalError(std::string error)
    {
        std::cout << error << std::endl;
        std::cout << "Press any key to quit..." << std::endl;
        int temp;
        std::cin >> temp;
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
}
