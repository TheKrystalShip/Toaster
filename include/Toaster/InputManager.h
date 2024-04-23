#pragma once

#include <GLM/glm.hpp>

#include <unordered_map>

namespace Toaster
{
    class InputManager
    {
    public:
        typedef unsigned int keyId_t;
        InputManager();
        ~InputManager();

        void update();

        void pressKey(keyId_t keyId);
        void releaseKey(keyId_t keyId);

        // Return true if the key is held down
        bool isKeyDown(keyId_t keyId);

        // Returns true if the key was just pressed
        bool isKeyPressed(keyId_t keyId);

        void setMouseCoords(float x, float y);
        glm::vec2 getMouseCoords() const { return _mouseCoords; }

    private:
        bool wasKeyDown(keyId_t keyId);

        std::unordered_map<keyId_t, bool> _keyMap;
        std::unordered_map<keyId_t, bool> _previousKeyMap;
        glm::vec2 _mouseCoords;
    };
}
