#pragma once

#include <GL/glew.h>

namespace Toaster
{
    struct Position
    {
        float x;
        float y;

        Position() : x(0), y(0)
        {
        }

        Position(float X, float Y) : x(X), y(Y)
        {
        }
    };

    struct ColorRGBA8
    {
        GLubyte r;
        GLubyte g;
        GLubyte b;
        GLubyte a;

        ColorRGBA8() : r(0), g(0), b(0), a(0)
        {
        }

        ColorRGBA8(GLubyte R, GLubyte G, GLubyte B, GLubyte A = 255) : r(R), g(G), b(B), a(A)
        {
        }
    };

    struct UV
    {
        float u;
        float v;

        UV() : u(0), v(0)
        {
        }

        UV(float U, float V) : u(U), v(V)
        {
        }
    };

    struct Vertex
    {
        Position position;
        ColorRGBA8 color = {0, 0, 0, 255};
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
