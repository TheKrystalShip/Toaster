#pragma once

#include "Texture2D.h"

#include <string>
#include <map>

namespace Toaster
{
    class TextureCache
    {
    public:
        TextureCache();
        ~TextureCache();

        Texture2D getTexture(std::string texturePath);
    private:
        std::map<std::string, Texture2D> _textureMap;
    };
}
