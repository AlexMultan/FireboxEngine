#version 460 core
    
    in vec2 TexCoords;
    out vec4 FragColor;

    uniform vec4 u_WireColor;
    uniform vec4 u_FaceColor;
    uniform float u_LineWidth;

    void main()
    {
        vec2 d = fwidth(TexCoords);
        vec2 gridA = smoothstep(vec2(0.0), d * u_LineWidth, TexCoords);
        vec2 gridB = smoothstep(vec2(0.0), d * u_LineWidth, 1.0 - TexCoords);

        float edge = min(min(gridA.x, gridA.y), min(gridB.x, gridB.y));
        float isEdge = 1.0 - edge;

        FragColor = mix(u_FaceColor, u_WireColor, isEdge);
    }