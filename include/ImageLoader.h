#pragma once

#include "GLTexture.h"

#include <string>

namespace Toaster
{
    class ImageLoader
    {
    public:
        static GLTexture loadPNG(std::string filePath);
    };
}
