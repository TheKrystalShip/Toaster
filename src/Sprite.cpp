#include "Sprite.h"
#include "Vertex.h"
#include "ResourceManager.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <cstddef>
#include <string>

namespace Toaster
{
    Sprite::Sprite()
    {
        _vboId = 0;
    }

    Sprite::~Sprite()
    {
        // Free the buffer from the GPU when Sprite object is destroyed
        if (_vboId != 0)
            glDeleteBuffers(1, &_vboId);
    }

    void Sprite::init(float x, float y, float width, float height, std::string texturePath)
    {
        _posX = x;
        _posY = y;
        _width = width;
        _height = height;

        _texture = ResourceManager::getTexture(texturePath);

        if (_vboId == 0)
            glGenBuffers(1, &_vboId);

        // Assume sprite is a square, draw 2 triangles
        Vertex vertexData[6];

        // First triangle
        vertexData[0].setPosition({_posX + _width, _posY + _height});
        vertexData[0].setUV({1.0f, 1.0f});

        vertexData[1].setPosition({_posX, _posY + _height});
        vertexData[1].setUV({0.f, 1.0f});

        vertexData[2].setPosition({_posX, _posY});
        vertexData[2].setUV({0.f, 0.f});

        // Seconds triangle
        vertexData[3].setPosition({_posX, _posY});
        vertexData[3].setUV({0.f, 0.f});

        vertexData[4].setPosition({_posX + _width, _posY});
        vertexData[4].setUV({1.0f, 0.f});

        vertexData[5].setPosition({_posX + _width, _posY + _height});
        vertexData[5].setUV({1.0f, 1.0f});
        // ColorRGBA8
        /*
         * Order
         * [0]: Top Right       (first triangle)
         * [1]: Top Left        (first triangle)
         * [2]: Bottom Left     (first triangle)
         * [3]: Bottom Left     (seconds triangle)
         * [4]: Bottom Right    (seconds triangle)
         * [5]: Top Right       (seconds triangle)
         */

        for (auto &v : vertexData)
            v.setColor({255, 0, 255, 255});

        // vertexData[0].setColor({0, 0, 0, 255});
        vertexData[1].setColor({0, 0, 255, 255});
        // vertexData[2].setColor({0, 0, 0, 255});
        // vertexData[3].setColor({0, 0, 0, 255});
        vertexData[4].setColor({0, 255, 0, 255});
        // vertexData[5].setColor({0, 0, 0, 255});

        glBindBuffer(GL_ARRAY_BUFFER, _vboId);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

        // Optional: Unbind buffer
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void Sprite::draw()
    {
        glBindTexture(GL_TEXTURE_2D, _texture.id);

        glBindBuffer(GL_ARRAY_BUFFER, _vboId);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        // Position pointer
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));

        // ColorRGBA8 pointer
        glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, color));

        // UV pointer
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));

        glDrawArrays(GL_TRIANGLES, 0, 6);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
