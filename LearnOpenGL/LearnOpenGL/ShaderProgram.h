#pragma once

#include <glad/glad.h> // 包含glad来获取所有的必须OpenGL头文件

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

    // 使用程序
    const ShaderProgram& use();

    // uniform工具函数
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

