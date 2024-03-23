#pragma once

#include "TextureCache.h"
#include "GLTexture.h"

#include <GL/glew.h>

#include <string>

namespace Toaster
{
    class ResourceManager
    {
    public:
        static GLTexture getTexture(std::string texturePath);

    private:
        static TextureCache _textureCache;
    };
}
