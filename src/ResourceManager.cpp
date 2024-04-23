#include "ResourceManager.h"

namespace Toaster
{
    TextureCache ResourceManager::_textureCache;

    Texture2D ResourceManager::getTexture(std::string texturePath)
    {
        return _textureCache.getTexture(texturePath);
    }
}
