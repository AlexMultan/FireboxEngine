#version 460 core

layout(location = 0) out vec3 gPosition;
layout(location = 1) out vec3 gNormal;
layout(location = 2) out vec4 gAlbedoSpec;

struct Material {
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    sampler2D normal;
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
	gNormal = worldNormal;
	gAlbedoSpec.rgb = texture(u_Material.diffuse, TexCoords).rgb;
	gAlbedoSpec.a = texture(u_Material.specular, TexCoords).r;
}