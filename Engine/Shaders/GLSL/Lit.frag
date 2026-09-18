#version 460 core

out vec4 FragColor;

struct DirectionalLight {
    vec3 direction;
    vec3 color;
    float intensity;
}; 

struct PointLight {
    vec3 position;
    vec4 color;
    float intensity;
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
uniform sampler2D u_SSAO;

uniform DirectionalLight u_DirectionalLight; 
uniform PointLight u_PointLights[MAX_POINT_LIGHTS];
uniform SpotLight u_SpotLights[MAX_SPOT_LIGHTS];
uniform vec3 u_ViewPos;
uniform PostProcessSettings u_PostProcessSettings;

const float PI = 3.14159265359;

layout (std140, binding = 0) uniform ShadowUniformBlock
{
    mat4 LighSpaceMatrices[16];
};

uniform float u_CascadePlaneDistances[16];
uniform int u_CascadeCount;
uniform float u_FarPlane;
uniform sampler2DArray u_ShadowMap;
uniform mat4 u_View;

const vec2 POISSON_DISK[32] = vec2[](
    vec2(0.27885360, -0.94997849),  vec2(-0.44994136, -0.55357852),
    vec2(0.47294243, 0.35339897),   vec2(-0.15615636, -0.94040556),
    vec2(-0.56272405, 0.01071058),  vec2(0.29976888, 0.08988296),
    vec2(0.91442614, -0.32681091),  vec2(0.07245618, 0.94623153),
    vec2(-0.24293125, 0.10408126),  vec2(0.72341380, 0.15470429),
    vec2(-0.84041605, -0.53441823), vec2(0.27136889, -0.27033564),
    vec2(-0.46604436, 0.87330918),  vec2(-0.65772270, 0.45825360),
    vec2(0.11389949, 0.36922850),   vec2(0.99507521, 0.01905259),
    vec2(0.58415873, -0.15568007),  vec2(-0.87294459, -0.23676143),
    vec2(0.00117223, -0.64269624),  vec2(0.53166886, -0.74321707),
    vec2(-0.19475744, -0.32139479), vec2(-0.88566945, 0.16835519),
    vec2(-0.36764561, 0.50372898),  vec2(0.59224461, 0.72140516),
    vec2(-0.08707635, 0.60283320),  vec2(0.79441621, 0.48731088),
    vec2(0.27117021, 0.65741462),   vec2(0.04290243, -0.08391496),
    vec2(0.63042878, -0.46535053),  vec2(-0.45608826, -0.85062513),
    vec2(-0.57244003, -0.28684735), vec2(0.28800010, -0.57297263)
);

float randomAngle(vec3 seed)
{
    return fract(sin(dot(seed, vec3(12.9898, 78.233, 45.5432))) * 43758.5453) * 6.28318530718;
}

float CalculateShadow(vec3 lightDirection, vec3 normal, vec3 fragPosWorldSpace)
{
    if (length(fragPosWorldSpace) < 0.0001)
    {
        return 0.0;
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
        return 0.0;
    }

    vec3 lightDir = normalize(-lightDirection);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    const float biasModifier = 0.5f;
    float currentDistance = (layer < u_CascadeCount) ? u_CascadePlaneDistances[layer] : u_FarPlane;
    bias *= 1.0 / (currentDistance * biasModifier);

    float shadow = 0.0;
    vec2 texelSize = 1.0 / vec2(textureSize(u_ShadowMap, 0));
    float filterRadius = 1.5 * (1.0 / float(layer + 1));
    float angle = randomAngle(fragPosWorldSpace);
    mat2 rot = mat2(cos(angle), -sin(angle), sin(angle), cos(angle));

    for (int i = 0; i < 32; i++)
    {
        vec2 offset = rot * POISSON_DISK[i] * texelSize * filterRadius;
        float pcfDepth = texture(u_ShadowMap, vec3(projCoords.xy + offset, layer)).r;
        shadow += (currentDepth - bias) > pcfDepth ? 1.0 : 0.0;
    }

    return shadow / 32.0;
}

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

vec3 CookTorranceDirectional(vec3 N, vec3 V, vec3 lightDir, vec3 radiance, vec3 albedo, float metallic, float roughness)
{
    vec3 L = normalize(lightDir);
    vec3 H = normalize(V + L);

    vec3 F0 = mix(vec3(0.04), albedo, metallic);

    float NDF = DistributionGGX(N, H, roughness);
    float G = GeometrySmith(N, V, L, roughness);
    vec3 F = FresnelSchlick(max(dot(H, V), 0.0), F0);

    vec3 nom = NDF * G * F;
    float denom = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001;
    vec3 specular = nom / denom;

    vec3 kS = F;
    vec3 kD = (vec3(1.0) - kS) * (1.0 - metallic);

    float NdotL = max(dot(N, L), 0.0);

    vec3 Lo = (kD * albedo / PI + specular) * radiance * NdotL;
    return Lo;
}

vec3 CookTorrancePointLight(vec3 N, vec3 V, vec3 lightPos, vec3 worldPos, vec3 albedo, float metallic, float roughness, vec3 radiance)
{
    vec3 F0 = mix(vec3(0.04), albedo, metallic);
    vec3 L = normalize(lightPos - worldPos);
    vec3 H = normalize(V + L);

    float NDF = DistributionGGX(N, H, roughness);
    float G = GeometrySmith(N, V, L, roughness);
    vec3 F = FresnelSchlick(max(dot(H, V), 0.0), F0);

    vec3 nom = NDF * G * F;
    float denom = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001;
    vec3 specular = nom / denom;

    vec3 kS = F;
    vec3 kD = (vec3(1.0) - kS) * (1.0 - metallic);

    float NdotL = max(dot(N, L), 0.0);

    vec3 Lo = (kD * albedo / PI + specular) * radiance * NdotL;
    return Lo;
}

vec3 CalculateDirectionalLight(DirectionalLight directionalLight, vec3 viewDir, vec3 normal, float shadow, vec3 albedo, float roughness, 
    float metallic, float ssao)
{
    vec3 directionalLightDir = normalize(-directionalLight.direction);
    vec3 N = normalize(normal);
    vec3 radiance =  directionalLight.color * directionalLight.intensity;

    vec3 Lo = CookTorranceDirectional(N, viewDir, directionalLightDir, radiance, albedo, metallic, roughness);
    vec3 ambient = vec3(0.03) * albedo * ssao;
    vec3 color = ambient + (1.0 - shadow) * Lo;
    return color;
}

vec3 CalculatePointLight(PointLight pointLight, vec3 fragPos, vec3 viewDir, vec3 albedo, float roughness, float ssao, vec3 normal, float metallic)
{
    vec3 N = normalize(normal);
    float dist = length(fragPos);
    float attenuation = 1.0 / (pointLight.constant + pointLight.linear * dist + pointLight.quadratic * (dist * dist));
    vec3 radiance = pointLight.color.rgb * attenuation * pointLight.intensity;
    vec3 Lo = CookTorrancePointLight(N, viewDir, pointLight.position, fragPos, albedo, metallic, roughness, radiance);
    vec3 ambient = vec3(0.03) * albedo * ssao;
    vec3 color = ambient + Lo;

    return color;
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

    vec3 Normal = texture(u_gNormalMetallic, TexCoords).rgb * 2.0 - 1.0;
    float Metallic = texture(u_gNormalMetallic, TexCoords).a;
    vec3 Albedo = pow(texture(u_gAlbedoRough, TexCoords).rgb, vec3(2.2));
    float Roughness = texture(u_gAlbedoRough, TexCoords).a;
    float AmbientOcclusion = texture(u_SSAO, TexCoords).r;
    float ao = texture(u_gAmbientOcclusion, TexCoords).r;
    vec3 viewDir = normalize(u_ViewPos - FragPos);

    float shadow = CalculateShadow(u_DirectionalLight.direction, Normal, FragPos);

    vec3 result = CalculateDirectionalLight(u_DirectionalLight, viewDir, Normal, shadow, Albedo, 
        Roughness, Metallic, u_PostProcessSettings.enableSSAO ? AmbientOcclusion : 1.0);

    if (u_NumberOfPointLights > 0)
    {
        for (int i = 0; i < MAX_POINT_LIGHTS; i++)
        {
            if (i >= u_NumberOfPointLights) break;
            result += CalculatePointLight(u_PointLights[i], FragPos, viewDir, Albedo, 
                Roughness, AmbientOcclusion, Normal, Metallic);
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

    result /= (result + vec3(1.0));
    result = pow(result.rgb, vec3(1.0 / max(u_PostProcessSettings.gamma, 0.0001)));
    FragColor = vec4(result, 1.0);
}