#pragma once

#include "Vertex.h"

#include <GLM/glm.hpp>
#include <GL/glew.h>

#include <vector>

namespace Toaster
{
    enum class GlyphSortType
    {
        NONE,
        FRONT_TO_BACK,
        BACK_TO_FRONT,
        TEXTURE
    };

    class Glyph
    {
    public:
        Glyph() {};
        Glyph(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint Texture, float Depth, const ColorRGBA8 &color) : texture(Texture), depth(Depth)
        {
            topLeft.setColor(color);
            topLeft.setPosition({destRect.x, destRect.y + destRect.w});
            topLeft.setUV({uvRect.x, uvRect.y + uvRect.w});

            bottomLeft.setColor(color);
            bottomLeft.setPosition({destRect.x, destRect.y});
            bottomLeft.setUV({uvRect.x, uvRect.y});

            bottomRight.setColor(color);
            bottomRight.setPosition({destRect.x + destRect.z, destRect.y});
            bottomRight.setUV({uvRect.x + uvRect.z, uvRect.y});

            topRight.setColor(color);
            topRight.setPosition({destRect.x + destRect.z, destRect.y + destRect.w});
            topRight.setUV({uvRect.x + uvRect.z, uvRect.y + uvRect.w});
        }

        GLuint texture;
        float depth;

        Vertex topLeft;
        Vertex bottomLeft;
        Vertex topRight;
        Vertex bottomRight;
    };

    class RenderBatch
    {
    public:
        RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) : offset(Offset), numVertices(NumVertices), texture(Texture)
        {
        }

        GLuint offset;
        GLuint numVertices;
        GLuint texture;
    };

    class SpriteBatch
    {
    public:
        SpriteBatch();
        ~SpriteBatch();

        void init();

        void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
        void end();

        void draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture, float depth, const ColorRGBA8 &color);

        void renderBatch();

    private:
        void createRenderBatches();
        void createVertexArray();
        void sortGlyphs();

        GLuint _vbo;
        GLuint _vao;

        GlyphSortType _sortType;

        // For fast sorting
        std::vector<Glyph *> _glyphPointers;

        // Actual values
        std::vector<Glyph> _glyphs;

        std::vector<RenderBatch> _renderBatches;
    };
}
