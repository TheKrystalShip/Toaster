#pragma once

#include "Texture2D.h"

#include <GL/glew.h>

#include <string>

namespace Toaster
{
    class Sprite
    {
    public:
        Sprite();
        ~Sprite();

        void init(float x, float y, float width, float height, std::string texturePath);
        void draw();

    private:
        float _posX;
        float _posY;
        float _width;
        float _height;
        GLuint _vboId;
        Texture2D _texture;
    };
}
