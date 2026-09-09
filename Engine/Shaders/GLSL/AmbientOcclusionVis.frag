#version 460 core

out vec4 FragColor;

uniform sampler2D u_SSAO;

in vec2 TexCoords;

void main()
{
    FragColor = vec4(vec3(texture(u_SSAO, TexCoords).r), 1.0);
}