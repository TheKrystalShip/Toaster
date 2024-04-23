#pragma once

#include "Texture2D.h"

#include <string>

namespace Toaster
{
    class ImageLoader
    {
    public:
        static Texture2D loadPNG(std::string filePath);
    };
}
