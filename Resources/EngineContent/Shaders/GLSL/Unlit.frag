#version 460 core

    out vec4 FragColor;

    uniform sampler2D gAlbedoSpec;

    in vec2 TexCoords;

    void main()
    {
        FragColor = vec4(texture(gAlbedoSpec, TexCoords).rgb, 1.0);
    }