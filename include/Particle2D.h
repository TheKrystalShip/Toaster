#pragma once

#include "Vertex.h"

#include <GLM/glm.hpp>

namespace Toaster
{
    // Keep this class as small as possible to improve cache friendly loading
    class Particle2D
    {
    public:
        friend class ParticleBatch2D;

        Particle2D();
        ~Particle2D();

        void update(float deltaTime);

    private:
        glm::vec2 _position = glm::vec2(0.0f);
        glm::vec2 _velocity = glm::vec2(0.0f);
        ColorRGBA8 _color;
        float _life = 0.0f;
        float _width = 0.0f;
    };
}
