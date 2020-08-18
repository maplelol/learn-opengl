#version 330 core

in vec3 oFragColor;
in vec2 oTexCoord;

uniform sampler2D mainTexture;
uniform sampler2D overlapTexture;

out vec4 FragColor;

void main()
{
    FragColor = mix(texture(mainTexture, oTexCoord), texture(overlapTexture, oTexCoord), 0.2);
}
