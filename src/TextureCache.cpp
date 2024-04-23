#include "TextureCache.h"
#include "Texture2D.h"
#include "ImageLoader.h"

#include <string>
#include <map>
#include <iostream>

namespace Toaster
{
    TextureCache::TextureCache()
    {
    }

    TextureCache::~TextureCache()
    {
    }

    Texture2D TextureCache::getTexture(std::string texturePath)
    {
        auto mit = _textureMap.find(texturePath);

        // Texture not found in cache, load it and save it
        if (mit == _textureMap.end())
        {
            Texture2D newTexture = ImageLoader::loadPNG(texturePath);
            _textureMap.insert({texturePath, newTexture});

            return newTexture;
        }

        return mit->second;
    }
}
