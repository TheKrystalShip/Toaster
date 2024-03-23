#pragma once

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

namespace Toaster
{
    class Camera2D
    {
    public:
        Camera2D();
        ~Camera2D();

        void init(int screenWidth, int screenHeight);

        glm::mat4 getCameraMatrix() { return _cameraMatrix; }

        float getScale() { return _scale; }
        void setScale(float newScale)
        {
            _scale = newScale;
            _needsMatrixUpdate = true;
        }

        glm::vec2 getPosition() { return _position; }
        void setPosition(const glm::vec2 &newPosition)
        {
            _position = newPosition;
            _needsMatrixUpdate = true;
        }

        glm::vec2 convertScreenToWorld(glm::vec2 screenCoords);

        void update();

        bool isBoxInView(const glm::vec2 &position, const glm::vec2 &dimensions);

    private:
        int _screenWidth;
        int _screenHeight;

        bool _needsMatrixUpdate;
        float _scale;

        glm::vec2 _position;
        glm::mat4 _cameraMatrix;
        glm::mat4 _orthoMatrix;
    };
}
