#version 460 core

    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aNormal;
    layout (location = 2) in vec2 aTexCoords;
    layout (location = 3) in vec3 aTangent;
    layout (location = 4) in vec3 aBitangent;
    layout (location = 5) in ivec4 aBoneIDs;
    layout (location = 6) in vec4 aWeights;
    
    uniform mat4 u_ViewProjection;
    uniform mat4 u_Model;
    uniform mat3 u_InverseNormal;
    uniform float u_Tiling;

    const int MAX_BONES = 100;
    const int MAX_BONE_INFLUENCE = 4;
    uniform mat4 u_FinalBoneMatrices[MAX_BONES];

    out vec3 FragPos;
    out vec2 TexCoords;
    out mat3 TBN;
    out vec3 Normal;

    void main()
    {
        FragPos = vec3(u_Model * vec4(aPos, 1.0));
        vec3 N = normalize(u_InverseNormal * aNormal);
        vec3 T = normalize(u_InverseNormal * aTangent);
        T = normalize(T - dot(T, N) * N);
        vec3 B = cross(N, T);
        if(dot(cross(N, T), normalize(u_InverseNormal * aBitangent)) < 0.0){
            T = T * -1.0;
        }
        TBN = mat3(T, B, N);
        TexCoords = aTexCoords * u_Tiling;
        Normal = N;

        vec4 totalPos = vec4(0.0);
        float totalWeight = 0.0;
        for(int i = 0; i < MAX_BONE_INFLUENCE; i++){
            if(aBoneIDs[i] == -1){
                continue;
            }
            if(aBoneIDs[i] > MAX_BONES){
                totalPos = vec4(aPos, 1.0);
                totalWeight = 1.0;
                break;
            }
            vec4 localPos = u_FinalBoneMatrices[aBoneIDs[i]] * vec4(aPos, 1.0);
            totalPos += localPos * aWeights[i];
            totalWeight += aWeights[i];
        }
        if(totalWeight < 0.0001){
            totalPos = vec4(aPos, 1.0);
        }
        gl_Position = u_ViewProjection * u_Model * totalPos;
    }