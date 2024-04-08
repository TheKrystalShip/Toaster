#pragma once

#include "Vertex.h"
#include "GLSLProgram.h"

#include <GLM/glm.hpp>

#include <vector>

namespace Toaster
{
    class DebugRenderer
    {
    public:
        DebugRenderer();
        ~DebugRenderer();

        void init();
        void end();

        void drawBox(const glm::vec4 &destRect, const ColorRGBA8 &color, float angle);
        void drawCircle(const glm::vec2 &center, const ColorRGBA8 &color, float radius);

        void render(const glm::mat4 &projectionMatrix, float lineWidth);
        void dispose();

        struct DebugVertex {
            glm::vec2 position;
            Toaster::ColorRGBA8 color;
        };

    private:
        Toaster::GLSLProgram _program;
        std::vector<DebugVertex> _verts;
        std::vector<GLuint> _indices;

        GLuint _vbo = 0; //< Vertex buffer object
        GLuint _vao = 0; //< Vertex array object
        GLuint _ibo = 0; //< Index buffer object
        int _numElements = 0;
    };
}
