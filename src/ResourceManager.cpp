#include "ResourceManager.h"

namespace Toaster
{
    TextureCache ResourceManager::_textureCache;

    GLTexture ResourceManager::getTexture(std::string texturePath)
    {
        return _textureCache.getTexture(texturePath);
    }
}
