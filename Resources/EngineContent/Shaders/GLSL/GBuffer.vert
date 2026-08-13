#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;
layout (location = 5) in ivec4 aBoneIDs;
layout (location = 6) in vec4 aWeights;

out vec3 FragPos;
out vec2 TexCoords;
out mat3 TBN;
out vec3 Normal;

uniform mat4 u_Model;
uniform mat4 u_ViewProjection;
uniform mat3 u_InverseNormal;
const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 u_FinalBoneMatrices[MAX_BONES];

void main()
{
    vec4 totalPos = vec4(0.0);
    vec3 totalNormal = vec3(0.0);
    float totalWeight = 0.0;
    for(int i = 0; i < MAX_BONE_INFLUENCE; i++)
    {
        if(aBoneIDs[i] == -1)
        {
            continue;
        }
        if(aBoneIDs[i] > MAX_BONES)
        {
            totalPos = vec4(aPos, 1.0);
            totalNormal = aNormal;
            totalWeight = 1.0;
            break;
        }
        mat4 boneMat = u_FinalBoneMatrices[aBoneIDs[i]];
        totalPos += (boneMat * vec4(aPos, 1.0)) * aWeights[i];
        totalNormal += mat3(boneMat) * aNormal * aWeights[i];
        totalWeight += aWeights[i];
    }
    if(totalWeight < 0.0001)
    {
        totalPos = vec4(aPos, 1.0);
        totalNormal = aNormal;
    }

    vec4 worldPos = u_Model * totalPos;
    FragPos = worldPos.xyz;

	TexCoords = aTexCoords;
	vec3 N = normalize(u_InverseNormal * totalNormal);
    vec3 T = u_InverseNormal * aTangent;
    if (dot(T, T) < 1e-8) T = vec3(1,0,0);
        T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
    if(dot(cross(N, T), normalize(u_InverseNormal * aBitangent)) < 0.0){
        B = -B;
    }
    TBN = mat3(T, B, N);
    TexCoords = aTexCoords;
    Normal = N;

	gl_Position = u_ViewProjection * worldPos;
}