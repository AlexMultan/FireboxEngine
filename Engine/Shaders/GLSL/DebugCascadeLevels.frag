#version 460 core

out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D u_gPosition;
uniform mat4 u_View;
uniform float u_CascadePlaneDistances[16];
uniform int u_CascadeCount;

void main()
{
    vec3 FragPos = texture(u_gPosition, TexCoords).rgb;
    vec4 fragPosViewSpace = u_View * vec4(FragPos, 1.0);
    float depthValue = abs(fragPosViewSpace.z);

    int layer = -1;
    for(int i = 0; i < u_CascadeCount; i++)
    {
        if(depthValue < u_CascadePlaneDistances[i])
        {
            layer = i;
            break;
        }
    }

    if(layer == -1 || layer >= u_CascadeCount)
    {
        layer = u_CascadeCount - 1;
    }
        
    vec3 cascadeColors[4] = vec3[](
        vec3(1.0, 0.0, 0.0), // Red   = Layer 0 (Closest)
        vec3(0.0, 1.0, 0.0), // Green = Layer 1
        vec3(0.0, 0.0, 1.0), // Blue  = Layer 2
        vec3(1.0, 1.0, 0.0)  // Yellow= Layer 3 (Farthest)
    );
    FragColor = vec4(cascadeColors[layer], 1.0);
}