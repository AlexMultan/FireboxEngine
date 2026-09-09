#version 460 core

out vec4 FragColor;

uniform sampler2D u_gNormalMetallic;

in vec2 TexCoords;

void main()
{
    FragColor = vec4(vec3(texture(u_gNormalMetallic, TexCoords).a), 1.0);
}