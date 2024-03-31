#include "Particle2D.h"

namespace Toaster
{
    Particle2D::Particle2D()
    {
    }

    Particle2D::~Particle2D()
    {
    }

    void Particle2D::update(float deltaTime)
    {
        _position += _velocity * deltaTime;
    }
}
