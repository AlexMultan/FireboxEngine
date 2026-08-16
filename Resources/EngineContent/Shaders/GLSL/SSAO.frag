#version 460 core

out float FragColor;

uniform sampler2D u_gPosition;
uniform sampler2D u_gNormal;
uniform sampler2D u_NoiseTexture;
uniform vec3 u_Samples[64];
uniform int u_KernelSize = 64;
uniform float u_Radius = 0.5;
uniform float u_Bias = 0.025;
uniform float u_Intensity = 0.5f;
uniform vec2 u_ScreenDimensions;
uniform mat4 u_Projection;

in vec2 TexCoords;

void main()
{
    vec2 noiseScale = vec2(u_ScreenDimensions.x / 4.0, u_ScreenDimensions.y / 4.0);
    vec3 fragPos = texture(u_gPosition, TexCoords).rgb;
    vec3 normal = normalize(texture(u_gNormal, TexCoords * noiseScale).rgb);
    vec3 randomVector = normalize(texture(u_NoiseTexture, TexCoords * noiseScale).rgb);
    vec3 tangent = normalize(randomVector - normal * dot(randomVector, normal));
    vec3 bitangent = cross(normal, tangent);
    mat3 TBN = mat3(tangent, bitangent, normal);

    float occlusion = 0.0;
    for(int i = 0; i < u_KernelSize; i++)
    {
        vec3 samplePosition = TBN * u_Samples[i];
        samplePosition = fragPos + samplePosition * u_Radius;
        vec4 offset = vec4(samplePosition, 1.0);
        offset = u_Projection * offset;
        offset.xyz /= offset.w;
        offset.xyz = offset.xyz * 0.5 + 0.5;

        float sampleDepth = texture(u_gPosition, offset.xy).z;
        float rangeCheck = smoothstep(0.0, 1.0, u_Radius / abs(fragPos.z - sampleDepth));
        occlusion += (sampleDepth >= samplePosition.z + u_Bias ? 1.0 : 0.0) * rangeCheck;
    }
    occlusion = 1.0 - (occlusion / u_KernelSize);
    FragColor = pow(occlusion, u_Intensity);
}