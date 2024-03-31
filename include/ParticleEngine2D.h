#pragma once

#include "ParticleBatch2D.h"
#include "SpriteBatch.h"

#include <vector>

namespace Toaster
{
    class ParticleEngine2D
    {
    public:
        ParticleEngine2D();
        ~ParticleEngine2D();

        /// The ParticleEngine2D becomes responsible for pointer deallocation
        void addParticleBatch(ParticleBatch2D *particleBatch);

        void update(float deltaTime);

        void draw(SpriteBatch *spriteBatch);

    private:
        std::vector<ParticleBatch2D *> _batches;
    };
}
