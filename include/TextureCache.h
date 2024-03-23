#pragma once

#include "GLTexture.h"

#include <string>
#include <map>

namespace Toaster
{
    class TextureCache
    {
    public:
        TextureCache();
        ~TextureCache();

        GLTexture getTexture(std::string texturePath);
    private:
        std::map<std::string, GLTexture> _textureMap;
    };
}
