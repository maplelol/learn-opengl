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
		float vertices[] = {
			0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,   // ¶¥½Ç
			0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // ÓÒÏÂ½Ç
			-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // ×óÏÂ½Ç
		};

        _vao = 0;
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);

        unsigned int VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        /*unsigned int EBO;
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);*/

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
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
