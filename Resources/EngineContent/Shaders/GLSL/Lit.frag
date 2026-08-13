#version 460 core

out vec4 FragColor;

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
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
};

#define MAX_POINT_LIGHTS 32
#define MAX_SPOT_LIGHTS 32
uniform int u_NumberOfPointLights;
uniform int u_NumberOfSpotLights;
in vec2 TexCoords;

uniform sampler2D u_gPosition;
uniform sampler2D u_gNormal;
uniform sampler2D u_gAlbedoSpec;
uniform sampler2D u_ShadowMask;

uniform DirectionalLight u_DirectionalLight; 
uniform PointLight u_PointLights[MAX_POINT_LIGHTS];
uniform SpotLight u_SpotLights[MAX_SPOT_LIGHTS];
uniform vec3 u_ViewPos;
uniform PostProcessSettings u_PostProcessSettings;

vec3 CalculateDirectionalLight(DirectionalLight directionalLight, vec3 viewDir, vec3 normal, float shadow, 
    vec3 _diffuse, float _specular)
{
    vec3 directionalLightDir = normalize(-directionalLight.direction);
    float diff = max(dot(normal, directionalLightDir), 0.0);
    vec3 halfwayDir = normalize(directionalLightDir + viewDir);
    float spec = pow(max(dot(viewDir, halfwayDir), 0.0), 256.0);
    vec3 ambient = directionalLight.ambient * _diffuse;
    vec3 diffuse = directionalLight.diffuse * diff * _diffuse;
    vec3 specular = directionalLight.specular * spec * _specular;	
    return (ambient + (1.0 - shadow) * (diffuse + specular));
}

vec3 CalculatePointLight(PointLight pointLight, vec3 normal, vec3 fragPos, vec3 viewDir, 
    vec3 _diffuse, float _specular)
{
    vec3 pointLightDir = normalize(pointLight.position - fragPos);
    float diff = max(dot(normal, pointLightDir), 0.0);
    vec3 reflectDir = reflect(-pointLightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256.0);
    vec3 ambient = pointLight.ambient * _diffuse;
    vec3 diffuse = pointLight.diffuse * diff * _diffuse;
    vec3 specular = pointLight.specular * spec * _specular;
    float distance = length(pointLight.position - fragPos);
    float attenuation = 1.0 / (pointLight.constant + pointLight.linear * distance + pointLight.quadratic * (distance * distance));    
    ambient *= attenuation;  
    diffuse *= attenuation;
    specular *= attenuation;   
    return (ambient + diffuse + specular);
}

vec3 CalculateSpotLight(SpotLight spotLight, vec3 normal, vec3 fragPos, vec3 viewDir, float shadow, 
    vec3 _diffuse, float _specular)
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
    vec3 ambient = spotLight.ambient * _diffuse;
    vec3 diffuse = spotLight.diffuse * diff * _diffuse;
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

    vec3 Normal = texture(u_gNormal, TexCoords).rgb;
    vec3 Diffuse = texture(u_gAlbedoSpec, TexCoords).rgb;
    float Specular = texture(u_gAlbedoSpec, TexCoords).a;
    vec3 viewDir = normalize(u_ViewPos - FragPos);

    float shadow = texture(u_ShadowMask, TexCoords).r;

    vec3 result = CalculateDirectionalLight(u_DirectionalLight, viewDir, Normal, shadow, Diffuse, Specular);

    if (u_NumberOfPointLights > 0)
    {
        for (int i = 0; i < MAX_POINT_LIGHTS; i++)
        {
            if (i >= u_NumberOfPointLights) break;
            result += CalculatePointLight(u_PointLights[i], Normal, FragPos, viewDir, Diffuse, Specular);
        }
    }

    if (u_NumberOfSpotLights > 0)
    {
        for (int i = 0; i < MAX_SPOT_LIGHTS; i++)
        {
            if (i >= u_NumberOfSpotLights) break;
            result += CalculateSpotLight(u_SpotLights[i], Normal, FragPos, viewDir, shadow, Diffuse, Specular);
        }
    }

    result = pow(result.rgb, vec3(1.0 / max(u_PostProcessSettings.gamma, 0.0001)));
    FragColor = vec4(result, 1.0);
}