#version 460 core

out vec4 FragColor;

struct DirectionalLight {
    vec3 direction;
    vec3 diffuse;
    vec3 ambient;
    vec3 specular;
}; 

struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
}; 

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    float constant;
    float linear;
    float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PostProcessSettings {
    float gamma;
    bool enableSSAO;
};

#define MAX_POINT_LIGHTS 32
#define MAX_SPOT_LIGHTS 32
uniform int u_NumberOfPointLights;
uniform int u_NumberOfSpotLights;
in vec2 TexCoords;

uniform sampler2D u_gPosition;
uniform sampler2D u_gNormalMetallic;
uniform sampler2D u_gAlbedoRough;
uniform sampler2D u_gAmbientOcclusion;
uniform sampler2D u_ShadowMask;
uniform sampler2D u_SSAO;

uniform DirectionalLight u_DirectionalLight; 
uniform PointLight u_PointLights[MAX_POINT_LIGHTS];
uniform SpotLight u_SpotLights[MAX_SPOT_LIGHTS];
uniform vec3 u_ViewPos;
uniform PostProcessSettings u_PostProcessSettings;

const float PI = 3.14159265359;

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;
    float nom = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
    return nom / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r * r) / 8.0;
    float nom = NdotV;
    float denom = NdotV * (1.0 - k) + k;
    return nom / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);
    return ggx1 * ggx2;
}

vec3 FresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

vec3 CalculateDirectionalLight(DirectionalLight directionalLight, vec3 viewDir, vec3 normal, float shadow, 
    vec3 _albedo, float _roughness, float ssao)
{
    vec3 directionalLightDir = normalize(-directionalLight.direction);
    float diff = max(dot(normal, directionalLightDir), 0.0);
    vec3 halfwayDir = normalize(directionalLightDir + viewDir);
    float spec = pow(max(dot(viewDir, halfwayDir), 0.0), 256.0);
    vec3 ambient = vec3(directionalLight.ambient * _albedo * ssao);
    vec3 diffuse = directionalLight.diffuse * diff * _albedo;
    vec3 specular = directionalLight.specular * spec * _roughness;
    return (ambient + (1.0 - shadow) * (diffuse + specular));
}

vec3 CalculatePointLight(PointLight pointLight, vec3 normal, vec3 fragPos, vec3 viewDir, 
    vec3 _albedo, float _specular, float ssao)
{
    vec3 pointLightDir = normalize(pointLight.position - fragPos);
    float diff = max(dot(normal, pointLightDir), 0.0);
    vec3 reflectDir = reflect(-pointLightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256.0);
    vec3 ambient = vec3(pointLight.ambient * _albedo * ssao);
    vec3 diffuse = pointLight.diffuse * diff * _albedo;
    vec3 specular = pointLight.specular * spec * _specular;
    float distance = length(pointLight.position - fragPos);
    float attenuation = 1.0 / (pointLight.constant + pointLight.linear * distance + pointLight.quadratic * (distance * distance));    
    ambient *= attenuation;  
    diffuse *= attenuation;
    specular *= attenuation;   
    return (ambient + diffuse + specular);
}

vec3 CalculateSpotLight(SpotLight spotLight, vec3 normal, vec3 fragPos, vec3 viewDir, float shadow, 
    vec3 _albedo, float _specular, float ssao)
{
    vec3 spotLightDir = normalize(spotLight.position - fragPos);
    float diff = max(dot(normal, spotLightDir), 0);
    vec3 reflectDir = reflect(-spotLightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256.0);
    float distance = length(spotLight.position - fragPos);
    float attenuation = 1.0 / (spotLight.constant + spotLight.linear * distance + spotLight.quadratic * (distance * distance));  
    float theta = dot(spotLightDir, normalize(-spotLight.direction));
    float epsilon = spotLight.cutOff - spotLight.outerCutOff;
    float intensity = clamp((theta - spotLight.outerCutOff) / epsilon, 0.0, 1.0);
    vec3 ambient = vec3(spotLight.ambient * _albedo * ssao);
    vec3 diffuse = spotLight.diffuse * diff * _albedo;
    vec3 specular = spotLight.specular * spec * _specular;
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + (1.0 - shadow) * (diffuse + specular));
} 

void main()
{
    vec3 FragPos = texture(u_gPosition, TexCoords).rgb;
    if (length(FragPos) < 0.0001)
        discard;

    vec3 Normal = texture(u_gNormalMetallic, TexCoords).rgb;
    float Metallic = texture(u_gNormalMetallic, TexCoords).a;
    vec3 Albedo = pow(texture(u_gAlbedoRough, TexCoords).rgb, vec3(2.2));
    float Roughness = texture(u_gAlbedoRough, TexCoords).a;
    float AmbientOcclusion = texture(u_SSAO, TexCoords).r;
    float ao = texture(u_gAmbientOcclusion, TexCoords).r;
    vec3 viewDir = normalize(u_ViewPos - FragPos);

    float shadow = texture(u_ShadowMask, TexCoords).r;

    vec3 result = CalculateDirectionalLight(u_DirectionalLight, viewDir, Normal, shadow, Albedo, 
        Roughness, u_PostProcessSettings.enableSSAO ? AmbientOcclusion : 1.0);

    if (u_NumberOfPointLights > 0)
    {
        for (int i = 0; i < MAX_POINT_LIGHTS; i++)
        {
            if (i >= u_NumberOfPointLights) break;
            result += CalculatePointLight(u_PointLights[i], Normal, FragPos, viewDir, Albedo, 
                Roughness, AmbientOcclusion);
        }
    }

    if (u_NumberOfSpotLights > 0)
    {
        for (int i = 0; i < MAX_SPOT_LIGHTS; i++)
        {
            if (i >= u_NumberOfSpotLights) break;
            result += CalculateSpotLight(u_SpotLights[i], Normal, FragPos, viewDir, shadow, 
                Albedo, Roughness, AmbientOcclusion);
        }
    }

    result = pow(result.rgb, vec3(1.0 / max(u_PostProcessSettings.gamma, 0.0001)));
    FragColor = vec4(result, 1.0);
}