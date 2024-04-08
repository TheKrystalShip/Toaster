#include "GLSLProgram.h"
#include "Errors.h"
#include "IOManager.h"

#include <GL/glew.h>

#include <string>
#include <fstream>
#include <vector>

namespace Toaster
{

    GLSLProgram::GLSLProgram() : _numAttributes(0), _programId(0), _vertexShaderId(0), _fragmentShaderId(0)
    {
    }

    GLSLProgram::~GLSLProgram()
    {
        dispose();
    }

    void GLSLProgram::compileShader(const char* source, GLuint shaderId)
    {
        glShaderSource(shaderId, 1, &source, nullptr);
        glCompileShader(shaderId);

        GLint success = 0;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

        // All ok
        if (success != GL_FALSE)
            return;

        // Problem loading shader, get the error message
        GLint maxLength = 0;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<char> errorLog(maxLength);
        glGetShaderInfoLog(shaderId, maxLength, &maxLength, &errorLog[0]);

        glDeleteShader(shaderId);

        std::printf("%s\n", &errorLog[0]);
        fatalError("Shader " + std::string(source) + " failed to compile");
    }

    void GLSLProgram::compileShader(const std::string &shaderFilePath, GLuint shaderId)
    {
        std::ifstream shaderFile(shaderFilePath);

        if (shaderFile.fail())
            fatalError("Failed to open " + shaderFilePath);

        std::string fileContent = "";
        std::string line;

        while (std::getline(shaderFile, line))
            fileContent += line + "\n";

        shaderFile.close();

        compileShader(fileContent.c_str(), shaderId);
    }

    void GLSLProgram::compileShaders(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath)
    {
        std::string vertSource;
        std::string fragSource;

        IOManager::readFileToBuffer(vertexShaderFilePath, vertSource);
        IOManager::readFileToBuffer(fragmentShaderFilePath, fragSource);

        compileShadersFromSource(vertSource.c_str(), fragSource.c_str());
    }

    void GLSLProgram::compileShadersFromSource(const char *vertexSource, const char *fragmentSource)
    {
        _programId = glCreateProgram();
        _vertexShaderId = glCreateShader(GL_VERTEX_SHADER);

        if (_vertexShaderId == 0)
            fatalError("glCreateShader(GL_VERTEX_SHADER) returned 0");

        _fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

        if (_fragmentShaderId == 0)
            fatalError("glCreateShader(GL_FRAGMENT_SHADER) returned 0");

        compileShader(vertexSource, _vertexShaderId);
        compileShader(fragmentSource, _fragmentShaderId);
    }

    void GLSLProgram::linkShaders()
    {
        // Attach shaders to program
        glAttachShader(_programId, _vertexShaderId);
        glAttachShader(_programId, _fragmentShaderId);

        // Link the program
        glLinkProgram(_programId);

        GLint isLinked = 0;
        glGetProgramiv(_programId, GL_LINK_STATUS, (int *)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<char> errorLog(maxLength);
            glGetProgramInfoLog(_programId, maxLength, &maxLength, &errorLog[0]);

            // Don't need program anymore
            glDeleteProgram(_programId);

            // Don't leak the shaders
            glDeleteShader(_vertexShaderId);
            glDeleteShader(_fragmentShaderId);

            std::printf("%s\n", &errorLog[0]);
            fatalError("Shaders failed to link!");
        }

        // Always detach after successful link
        glDetachShader(_programId, _vertexShaderId);
        glDetachShader(_programId, _fragmentShaderId);

        // Safe to also delete shaders after linking
        glDeleteShader(_vertexShaderId);
        glDeleteShader(_fragmentShaderId);
    }

    void GLSLProgram::addAttribute(const std::string &attributeName)
    {
        glBindAttribLocation(_programId, _numAttributes++, attributeName.c_str());
    }

    GLint GLSLProgram::getUniformLocation(const std::string uniformName)
    {
        GLuint location = glGetUniformLocation(_programId, uniformName.c_str());

        if (location == GL_INVALID_INDEX)
            fatalError("Uniform " + uniformName + " not found in shader");

        return location;
    }

    void GLSLProgram::bind()
    {
        glUseProgram(_programId);

        for (int i = 0; i < _numAttributes; i++)
            glEnableVertexAttribArray(i);
    }

    void GLSLProgram::unbind()
    {
        glUseProgram(0);

        for (int i = 0; i < _numAttributes; i++)
            glDisableVertexAttribArray(i);
    }

    void GLSLProgram::dispose()
    {
        if (_programId)
            glDeleteProgram(_programId);
    }
}
