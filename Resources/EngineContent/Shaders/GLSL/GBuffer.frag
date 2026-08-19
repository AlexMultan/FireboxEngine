#version 460 core

layout(location = 0) out vec3 gPosition;
layout(location = 1) out vec4 gNormalMetallic;
layout(location = 2) out vec4 gAlbedoRough;
layout(location = 3) out vec4 gAmbientOcclusion;

struct Material {
    vec3 ambient;
    sampler2D diffuse;
    vec4 diffuseColor;
    sampler2D specular;
    sampler2D normal;
    sampler2D roughness;
    float roughnessValue;
    sampler2D metallic;
    float metallicValue;
    sampler2D ambientOcclusion;

    bool hasDiffuse;
    bool hasRoughness;
    bool hasMetallic;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
in mat3 TBN;

uniform Material u_Material;

void main()
{
	gPosition = FragPos;
    vec3 normal;
    vec3 sampledNormal = texture(u_Material.normal, TexCoords).rgb;
    normal = normalize(sampledNormal * 2.0 - 1.0);
    vec3 worldNormal = normalize(TBN * normal);
	gNormalMetallic.rgb = worldNormal;
    gNormalMetallic.a = u_Material.hasMetallic ? texture(u_Material.metallic, TexCoords).r : u_Material.metallicValue;
	gAlbedoRough.rgb = u_Material.hasDiffuse ? texture(u_Material.diffuse, TexCoords).rgb : u_Material.diffuseColor.rgb;
	gAlbedoRough.a = u_Material.hasRoughness ? texture(u_Material.roughness, TexCoords).r : u_Material.roughnessValue;
    gAmbientOcclusion = texture(u_Material.ambientOcclusion, TexCoords);
}