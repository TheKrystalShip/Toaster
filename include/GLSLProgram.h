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
        void compileShadersFromSource(const char* vertexSource, const char* fragmentSource);
        void linkShaders();
        void addAttribute(const std::string& attributeName);

        GLint getUniformLocation(const std::string uniformName);

        void bind();
        void unbind();

        void dispose();

    private:
        void compileShader(const char* source, GLuint shaderId);
        void compileShader(const std::string& shaderFilePath, GLuint shaderId);

        int _numAttributes;
        GLuint _programId = 0;
        GLuint _vertexShaderId = 0;
        GLuint _fragmentShaderId = 0;
    };
}
