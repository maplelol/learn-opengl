#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
:_program(0){

}

ShaderProgram::~ShaderProgram() {
    if (_program > 0) {
        glDeleteProgram(_program);
        _program = 0;
    }
}

bool ShaderProgram::initWithPath(const GLchar* vertexPath, const GLchar* fragmentPath) {
    // 1. 从文件路径中获取顶点/片段着色器
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // 保证ifstream对象可以抛出异常：
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // 打开文件
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // 读取文件的缓冲内容到数据流中
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // 关闭文件处理器
        vShaderFile.close();
        fShaderFile.close();
        // 转换数据流到string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        return false;
    }

    return initWithCode(vertexCode.c_str(), fragmentCode.c_str());
}

bool ShaderProgram::initWithCode(const GLchar* vertexCode, const GLchar* fragmentCode) {
    GLuint vertex = _createShader(GL_VERTEX_SHADER, vertexCode);
    if (vertex == 0) { return false; }
    GLuint fragment = _createShader(GL_FRAGMENT_SHADER, fragmentCode);
    if (fragment == 0) { return false; }

    _program = _createProgram(vertex, fragment);
    if (_program == 0) { return false; }

    // 删除着色器，它们已经链接到我们的程序中了，已经不再需要了
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return true;
}

const ShaderProgram& ShaderProgram::use()
{
    glUseProgram(_program);
    return *this;
}

const ShaderProgram& ShaderProgram::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(_program, name.c_str()), (int)value);
    return *this;
}

const ShaderProgram& ShaderProgram::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(_program, name.c_str()), value);
    return *this;
}

const ShaderProgram& ShaderProgram::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(_program, name.c_str()), value);
    return *this;
}

const ShaderProgram& ShaderProgram::setFloat4(const std::string& name, float v1, float v2, float v3, float v4) const {
    glUniform4f(glGetUniformLocation(_program, name.c_str()), v1, v2, v3, v4);
    return *this;
}

GLuint ShaderProgram::_createShader(GLenum shaderType, const GLchar* shaderCode) {
    GLuint shader = glCreateShader(shaderType);

    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);

    int success = 0;
    char infoLog[512] = { 0 };
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        return 0;
    }

    return shader;
}

GLuint ShaderProgram::_createProgram(GLuint vertexShader, GLuint fragmentShader) {
    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success = 0;
    char infoLog[512] = {0};
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
        return 0;
    }

    return shaderProgram;
}
