#pragma once

#include "TextureCache.h"
#include "Texture2D.h"

#include <GL/glew.h>

#include <string>

namespace Toaster
{
    class ResourceManager
    {
    public:
        static Texture2D getTexture(std::string texturePath);

    private:
        static TextureCache _textureCache;
    };
}
