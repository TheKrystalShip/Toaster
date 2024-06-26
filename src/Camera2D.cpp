#include "Camera2D.h"

namespace Toaster
{
    Camera2D::Camera2D() : _screenWidth(1024),
                           _screenHeight(768),
                           _needsMatrixUpdate(true),
                           _scale(1.0f),
                           _position(0.0f, 0.0f),
                           _cameraMatrix(1.0f),
                           _orthoMatrix(1.0f)
    {
    }

    Camera2D::~Camera2D()
    {
    }

    void Camera2D::init(int screenWidth, int screenHeight)
    {
        _screenWidth = screenWidth;
        _screenHeight = screenHeight;
        _orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
    }

    glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenCoords)
    {
        // Invert Y
        screenCoords.y = _screenHeight - screenCoords.y;

        // Convert center of screen to 0,0
        screenCoords -= glm::vec2(_screenWidth / 2, _screenHeight / 2);
        screenCoords /= _scale;

        // Translate with camera position
        screenCoords += _position;

        return screenCoords;
    }

    void Camera2D::update()
    {
        if (!_needsMatrixUpdate)
            return;

        glm::vec3 translate(-_position.x + _screenWidth / 2, -_position.y + _screenHeight / 2, 0.0f);
        _cameraMatrix = glm::translate(_orthoMatrix, translate);

        glm::vec3 scale(_scale, _scale, 0.0f);
        _cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;

        _needsMatrixUpdate = false;
    }

    bool Camera2D::isBoxInView(const glm::vec2 &position, const glm::vec2 &dimensions)
    {
        glm::vec2 scaledScreenDimensions = glm::vec2(_screenWidth, _screenHeight) / (_scale * 0.9f);

        const float MIN_DISTANCE_X = (dimensions.x / 2.0f) + (scaledScreenDimensions.x / 2.0f);
        const float MIN_DISTANCE_Y = (dimensions.y / 2.0f) + (scaledScreenDimensions.y / 2.0f);

        glm::vec2 centerPos = position + (dimensions * 2.0f);
        glm::vec2 distVec = centerPos - _position;

        float xDepth = MIN_DISTANCE_X - std::abs(distVec.x);
        float yDepth = MIN_DISTANCE_Y - std::abs(distVec.y);

        return (xDepth > 0 && yDepth > 0);
    }
}
