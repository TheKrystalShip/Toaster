#pragma once

#include "GLTexture.h"
#include "Particle2D.h"
#include "SpriteBatch.h"
#include "Vertex.h"

#include <GLM/glm.hpp>

#include <functional>

namespace Toaster
{
    class ParticleBatch2D
    {
    public:
        ParticleBatch2D();
        ~ParticleBatch2D();

        void init(int maxParticles, float decayRate, GLTexture texture, std::function<void(Particle2D &, float)> updateParticleFunc = defaultUpdateParticleFunc);

        void update(float deltaTime);

        void draw(SpriteBatch *spriteBatch);

        void addParticle(const glm::vec2 &position, const glm::vec2 &velocity, const ColorRGBA8 &color, float width);

    private:
        int findFreeParticle();

        std::function<void(Particle2D &, float)> _updateParticleFunc;

        // How fast particle dissapear
        float _decayRate = 0.1f;

        // Keep big buffer for cache friendlyness & reusability
        Particle2D *_buffer = nullptr;
        int _maxParticles = 0;
        int _lastFreeParticle = 0;
        GLTexture _texture;
    };
}
