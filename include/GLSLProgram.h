#pragma once

#include <GL/glew.h>

#include <string>

namespace Toaster
{
    class GLSLProgram
    {
    public:
        GLSLProgram();
        ~GLSLProgram();

        void compileShaders(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath);
        void linkShaders();
        void addAttribute(const std::string& attributeName);

        GLint getUniformLocation(const std::string uniformName);

        void bind();
        void unbind();

    private:
        void compileShader(const std::string& shaderFilePath, GLuint shaderId);

        int _numAttributes;
        GLuint _programId;
        GLuint _vertexShaderId;
        GLuint _fragmentShaderId;
    };
}
