#version 460 core

    out vec4 FragColor;

    uniform float u_Near;
    uniform float u_Far;

    float LinearizeDepth(float depth)
    {
        return (u_Near * u_Far) / (depth * (u_Far - u_Near) + u_Near);
    }

    void main()
    {
        float linearDepth = LinearizeDepth(gl_FragCoord.z);
        float normalized = log(linearDepth + 1.0) / log(u_Far + 1.0);
        FragColor = vec4(vec3(normalized), 1.0);
    }