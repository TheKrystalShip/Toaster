#include "TextureCache.h"
#include "GLTexture.h"
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

    GLTexture TextureCache::getTexture(std::string texturePath)
    {
        auto mit = _textureMap.find(texturePath);

        // Texture not found in cache, load it and save it
        if (mit == _textureMap.end())
        {
            GLTexture newTexture = ImageLoader::loadPNG(texturePath);
            _textureMap.insert({texturePath, newTexture});

            return newTexture;
        }

        return mit->second;
    }
}
