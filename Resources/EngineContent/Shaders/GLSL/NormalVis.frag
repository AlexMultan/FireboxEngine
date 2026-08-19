#version 460 core

out vec4 FragColor;

uniform sampler2D u_gNormalMetallic;

in vec2 TexCoords;

void main()
{
    FragColor = vec4(texture(u_gNormalMetallic, TexCoords).rgb, 1.0);
}