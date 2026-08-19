#version 460 core

layout(location = 0) out float aShadowMask;

in vec2 TexCoords;

uniform sampler2D u_gPosition;
uniform sampler2D u_gNormalMetallic;
uniform mat4 u_View;

layout (std140, binding = 0) uniform ShadowUniformBlock
{
    mat4 LighSpaceMatrices[16];
};

uniform float u_CascadePlaneDistances[16];
uniform int u_CascadeCount;
uniform vec3 u_LightDirection;
uniform float u_FarPlane;
uniform sampler2DArray u_ShadowMap;

const vec2 POISSON_DISK[16] = vec2[](
    vec2(-0.94201624, -0.39906216), vec2(0.94558609, -0.76890725),
    vec2(-0.09418410, -0.92938870), vec2(0.34495938, 0.29387760),
    vec2(-0.91588581, 0.45771432),  vec2(-0.81544232, -0.87912464),
    vec2(-0.38277543, 0.27676845),  vec2(0.97484398, 0.75648377),
    vec2(0.44323325, -0.97511554),  vec2(0.53742981, -0.47373420),
    vec2(-0.26496911, -0.41893023), vec2(0.79197514, 0.19090160),
    vec2(-0.24188840, 0.99706507),  vec2(-0.81409955, 0.91437590),
    vec2(0.19984126, 0.78641367),   vec2(0.14383161, -0.14100790)
);

float randomAngle(vec3 seed)
{
    return fract(sin(dot(seed, vec3(12.9898, 78.233, 45.5432))) * 43758.5453) * 6.28318530718;
}

void main()
{
    vec3 fragPosWorldSpace = texture(u_gPosition, TexCoords).rgb;
    vec3 normal = texture(u_gNormalMetallic, TexCoords).rgb;

    if (length(fragPosWorldSpace) < 0.0001)
    {
        aShadowMask = 0.0;
        return;
    }

    vec4 fragPosViewSpace = u_View * vec4(fragPosWorldSpace, 1.0);
    float depthValue = abs(fragPosViewSpace.z);

    int layer = -1;
    for (int i = 0; i < u_CascadeCount; i++)
    {
        if (depthValue < u_CascadePlaneDistances[i])
        {
            layer = i;
            break;
        }
    }

    if (layer == -1 || layer >= u_CascadeCount)
    {
        layer = u_CascadeCount - 1;
    }

    vec4 fragPosLightSpace = LighSpaceMatrices[layer] * vec4(fragPosWorldSpace, 1.0);
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords.xy = projCoords.xy * 0.5 + 0.5;
    
    float currentDepth = projCoords.z;

    if (currentDepth > 1.0)
    {
        aShadowMask = 0.0;
        return;
    }

    vec3 lightDir = normalize(-u_LightDirection);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    const float biasModifier = 0.5f;
    float currentDistance = (layer < u_CascadeCount) ? u_CascadePlaneDistances[layer] : u_FarPlane;
    bias *= 1.0 / (currentDistance * biasModifier);

    float shadow = 0.0;
    vec2 texelSize = 1.0 / vec2(textureSize(u_ShadowMap, 0));
    float filterRadius = 1.5 * (1.0 / float(layer + 1));
    float angle = randomAngle(fragPosWorldSpace);
    mat2 rot = mat2(cos(angle), -sin(angle), sin(angle), cos(angle));

    for (int i = 0; i < 16; i++)
    {
        vec2 offset = rot * POISSON_DISK[i] * texelSize * filterRadius;
        float pcfDepth = texture(u_ShadowMap, vec3(projCoords.xy + offset, layer)).r;
        shadow += (currentDepth - bias) > pcfDepth ? 1.0 : 0.0;
    }

    aShadowMask = shadow / 16.0;
}