#pragma once

#include "Vertex.h"

#include <GL/glew.h>
#include <GLM/glm.hpp>

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
        Glyph(){};
        Glyph(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint Texture, float Depth, const ColorRGBA8 &color);
        Glyph(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint Texture, float Depth, const ColorRGBA8 &color, float angleRadiants);

        GLuint texture;
        float depth;

        Vertex topLeft;
        Vertex bottomLeft;
        Vertex topRight;
        Vertex bottomRight;

    private:
        glm::vec2 rotatePoint(glm::vec2 pos, float angleRadiants);
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
        void draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture, float depth, const ColorRGBA8 &color, float angleRadiants);
        void draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture, float depth, const ColorRGBA8 &color, const glm::vec2 &direction);

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
