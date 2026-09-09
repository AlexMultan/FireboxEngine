#version 460 core
			
    out vec4 FragColor;

    in vec3 TexCoords;

    uniform samplerCube u_SkyboxTex;

    void main()
    {
        FragColor = texture(u_SkyboxTex, TexCoords);
    }