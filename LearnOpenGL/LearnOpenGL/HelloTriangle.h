#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ShaderProgram.h"

class HelloTriangle {
private:
    GLuint _vao;
    ShaderProgram _shaderProgram;

public:
	inline bool prepare() {
		GLfloat vertices[] = {
			0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,   // ¶¥½Ç
			0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // ÓÒÏÂ½Ç
			-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // ×óÏÂ½Ç
		};

        _vao = 0;
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);

        GLuint vbo = 0;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        /*GLuint ebo = 0;
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);*/

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);

        if (!_shaderProgram.initWithPath("Shaders/Vertex1.vert", "Shaders/Fragment1.frag")) {
            return false;
        }

        return true;
	}

	inline void render() {
        _shaderProgram.use();

        glBindVertexArray(_vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
	}
};
