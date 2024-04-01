#pragma once

#include <GL/glew.h>

namespace Toaster
{
    struct Position
    {
        float x = 0.0f;
        float y = 0.0f;

        Position()
        {
        }

        Position(float X, float Y) : x(X), y(Y)
        {
        }
    };

    struct ColorRGBA8
    {
        GLubyte r = 255;
        GLubyte g = 255;
        GLubyte b = 255;
        GLubyte a = 255;

        ColorRGBA8()
        {
        }

        ColorRGBA8(GLubyte R, GLubyte G, GLubyte B, GLubyte A = 255) : r(R), g(G), b(B), a(A)
        {
        }
    };

    struct UV
    {
        float u = 0.0f;
        float v = 0.0f;

        UV()
        {
        }

        UV(float U, float V) : u(U), v(V)
        {
        }
    };

    struct Vertex
    {
        Position position;
        ColorRGBA8 color;
        UV uv;

        void setColor(ColorRGBA8 color)
        {
            this->color = color;
        }

        void setPosition(Position position)
        {
            this->position = position;
        }

        void setUV(UV uv)
        {
            this->uv = uv;
        }
    };
}
