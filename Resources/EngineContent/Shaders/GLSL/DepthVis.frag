#version 460 core

out vec4 FragColor;

uniform float u_Near;
uniform float u_Far;
uniform sampler2D u_gPosition;
uniform mat4 u_Projection;

in vec2 TexCoords;

float LinearizeDepth(float depth)
{
    return (u_Near * u_Far) / (depth * (u_Far - u_Near) + u_Near);
}

void main()
{
    vec3 worldPos = texture(u_gPosition, TexCoords).rgb;
    vec4 clipSpacePos = u_Projection * vec4(worldPos, 1.0);
    float ndcZ = clipSpacePos.z / clipSpacePos.w;
    float fragCoordZ = ndcZ * 0.5 + 0.5;
    float linearDepth = LinearizeDepth(gl_FragCoord.z);
    float normalized = log(linearDepth + 1.0) / log(u_Far + 1.0);
    FragColor = vec4(vec3(normalized), 1.0);
}