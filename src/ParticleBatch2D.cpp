#include "ParticleBatch2D.h"

namespace Toaster
{
    ParticleBatch2D::ParticleBatch2D()
    {
    }

    ParticleBatch2D::~ParticleBatch2D()
    {
        delete[] _buffer;
    }

    void ParticleBatch2D::init(int maxParticles, float decayRate, GLTexture texture)
    {
        _maxParticles = maxParticles;
        _buffer = new Particle2D[_maxParticles];

        _decayRate = decayRate;
        _texture = texture;
    }

    void ParticleBatch2D::update(float deltaTime)
    {
        for (int i = 0; i < _maxParticles; i++)
        {
            if (_buffer[i]._life > 0.0f)
            {
                _buffer[i].update(deltaTime);
                _buffer[i]._life -= _decayRate * deltaTime;
            }
        }
    }

    void ParticleBatch2D::draw(SpriteBatch *spriteBatch)
    {
        // Assume all particles have the same UV since we're not using a texture atlas yet
        glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
        for (int i = 0; i < _maxParticles; i++)
        {
            auto &p = _buffer[i];

            if (p._life > 0.0f)
            {
                glm::vec4 destRect(p._position.x, p._position.y, p._width, p._width);
                spriteBatch->draw(destRect, uvRect, _texture.id, 0.0f, p._color);
            }
        }
    }

    void ParticleBatch2D::addParticle(const glm::vec2 &position, const glm::vec2 &velocity, const ColorRGBA8 &color, float width)
    {
        int particleIndex = findFreeParticle();
        auto &p = _buffer[particleIndex];

        p._life = 1.0f;
        p._position = position;
        p._velocity = velocity;
        p._color = color;
        p._width = width;
    }

    int ParticleBatch2D::findFreeParticle()
    {
        // Iterate forwards from _lastFreeParticle
        for (int i = _lastFreeParticle; i < _maxParticles; i++)
        {
            if (_buffer[i]._life <= 0.0f)
            {
                _lastFreeParticle = i;
                return i;
            }
        }

        // Iterate from 0 to _lastFreeParticle
        for (int i = 0; i < _lastFreeParticle; i++)
        {
            if (_buffer[i]._life <= 0.0f)
            {
                _lastFreeParticle = i;
                return i;
            }
        }

        // No free particles were found
        return 0;
    }
}
