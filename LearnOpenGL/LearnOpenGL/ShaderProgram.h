#pragma once

#include <glad/glad.h> // ����glad����ȡ���еı���OpenGLͷ�ļ�

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class ShaderProgram
{
public:
    ShaderProgram();
    ~ShaderProgram();

    inline GLuint Id() { return _program; }

    bool initWithPath(const GLchar* vertexPath, const GLchar* fragmentPath);
    bool initWithCode(const GLchar* vertexCode, const GLchar* fragmentCode);

    // ʹ�ó���
    const ShaderProgram& use();

    // uniform���ߺ���
    const ShaderProgram& setBool(const std::string& name, bool value) const;
    const ShaderProgram& setInt(const std::string& name, int value) const;
    const ShaderProgram& setFloat(const std::string& name, float value) const;

    const ShaderProgram& setFloat4(const std::string& name, float v1, float v2, float v3, float v4) const;

private:
    GLuint _program;

private:
    GLuint _createShader(GLenum shaderType, const GLchar* shaderCode);
    GLuint _createProgram(GLuint vertexShader, GLuint fragmentShader);
};

