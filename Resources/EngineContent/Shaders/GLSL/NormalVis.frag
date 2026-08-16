#version 460 core

out vec4 FragColor;

uniform sampler2D u_gNormal;

in vec2 TexCoords;

void main()
{
    FragColor = vec4(texture(u_gNormal, TexCoords).rgb, 1.0);
}