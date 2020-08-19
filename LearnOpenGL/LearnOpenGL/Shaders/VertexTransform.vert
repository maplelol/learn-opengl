#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aVertexColor;
layout(location = 2) in vec2 aTexCoord;

out vec3 oFragColor;
out vec2 oTexCoord;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(aPos, 1.0);
	oFragColor = aVertexColor;
	oTexCoord = aTexCoord;
}
