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

        glm::vec2 position = glm::vec2(0.0f);
        glm::vec2 velocity = glm::vec2(0.0f);
        ColorRGBA8 color;
        float life = 0.0f;
        float width = 0.0f;
    };

    inline void defaultUpdateParticleFunc(Particle2D &p, float delatTime)
    {
        p.position += p.velocity * delatTime;
        p.color.a = (GLubyte)(p.life *255.0f);
    }
}
