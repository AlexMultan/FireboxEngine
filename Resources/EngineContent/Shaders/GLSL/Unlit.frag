#version 460 core

    out vec4 FragColor;

    uniform sampler2D u_Diffuse;

    in vec2 TexCoords;

    void main()
    {
        FragColor = vec4(texture(u_Diffuse, TexCoords));
    }