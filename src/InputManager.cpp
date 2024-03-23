#include "InputManager.h"

namespace Toaster
{
    InputManager::InputManager() : _mouseCoords(0.0f)
    {
    }

    InputManager::~InputManager()
    {
    }

    void InputManager::update()
    {
        for (auto &it : _keyMap)
        {
            _previousKeyMap[it.first] = it.second;
        }
    }

    void InputManager::pressKey(keyId_t keyId)
    {
        _keyMap[keyId] = true;
    }

    void InputManager::releaseKey(keyId_t keyId)
    {
        _keyMap[keyId] = false;
    }

    bool InputManager::isKeyPressed(keyId_t keyId)
    {
        return (isKeyDown(keyId) && !wasKeyDown(keyId));
    }

    void InputManager::setMouseCoords(float x, float y)
    {
        _mouseCoords.x = x;
        _mouseCoords.y = y;
    }

    bool InputManager::isKeyDown(keyId_t keyId)
    {
        auto it = _keyMap.find(keyId);

        if (it != _keyMap.end())
            return it->second;

        return false;
    }

    bool InputManager::wasKeyDown(keyId_t keyId)
    {
        auto it = _previousKeyMap.find(keyId);

        if (it != _previousKeyMap.end())
            return it->second;

        return false;
    }
}
