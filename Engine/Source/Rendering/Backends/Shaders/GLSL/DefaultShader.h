#pragma once

namespace Firebox::Shaders::GLSL {

	inline constexpr const char* DefaultVertex = R"(#version 460 core

		layout (location = 0) in vec3 aPos;
		layout (location = 1) in vec3 aNormal;
		layout (location = 2) in vec2 aTexCoords;
		layout (location = 3) in vec3 aTangent;
		layout (location = 4) in vec3 aBitangent;

		uniform mat4 u_ViewProjection;
		uniform mat4 u_Model;
		uniform mat3 u_InverseNormal;
		uniform float u_Tiling;

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
			gl_Position = u_ViewProjection * u_Model * vec4(aPos, 1.0);
		}
	)";

	inline constexpr const char* DefaultFragment = R"(#version 460 core

		out vec4 FragColor;

		struct Material {
			vec3 ambient;
			sampler2D diffuse;
			sampler2D specular;
			sampler2D normal;
			float shininess;
		};

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
		
		//#define NR_POINT_LIGHTS 1
		//uniform PointLight pointLights[NR_POINT_LIGHTS];

		in vec3 FragPos;
		in vec2 TexCoords;
		in mat3 TBN;
		in vec3 Normal;
		
		uniform Material u_Material;
		uniform DirectionalLight u_DirectionalLight; 
		uniform PointLight u_PointLight; 
		uniform vec3 u_ViewPos;
		uniform sampler2DArray u_ShadowMap;
		uniform float u_FarPlane;
		uniform mat4 u_View;

		layout (std140, binding = 0) uniform LightSpaceMatrices
		{
			mat4 LighSpaceMatrices[16];
		};

		uniform float u_CascadePlaneDistances[16];
		uniform int u_CascadeCount;

		vec3 CalculateDirectionalLight(DirectionalLight directionalLight, vec3 viewDir, vec3 normal, float shadow)
		{
			vec3 directionalLightDir = normalize(-directionalLight.direction);
			float diff = max(dot(normal, directionalLightDir), 0.0);
			vec3 halfwayDir = normalize(directionalLightDir + viewDir);
			float spec = pow(max(dot(viewDir, halfwayDir), 0.0), u_Material.shininess);
			vec3 ambient = directionalLight.ambient * texture(u_Material.diffuse, TexCoords).rgb;
			vec3 diffuse = directionalLight.diffuse * diff * texture(u_Material.diffuse, TexCoords).rgb;
			vec3 specular = directionalLight.specular * spec * texture(u_Material.specular, TexCoords).rgb;	
			return (ambient + (1.0 - shadow) * (diffuse + specular));
		}

		vec3 CalculatePointLight(PointLight pointLight, vec3 normal, vec3 fragPos, vec3 viewDir, float shadow)
		{
			vec3 pointLightDir = normalize(pointLight.position - fragPos);
			float diff = max(dot(normal, pointLightDir), 0.0);
			vec3 reflectDir = reflect(-pointLightDir, normal);
			float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
			vec3 ambient = pointLight.ambient * texture(u_Material.diffuse, TexCoords).rgb;
			vec3 diffuse = pointLight.diffuse * diff * texture(u_Material.diffuse, TexCoords).rgb;
			vec3 specular = pointLight.specular * spec * texture(u_Material.specular, TexCoords).rgb;
			float distance = length(pointLight.position - fragPos);
			float attenuation = 1.0 / (pointLight.constant + pointLight.linear * distance + pointLight.quadratic * (distance * distance));    
			ambient *= attenuation;  
			diffuse *= attenuation;
			specular *= attenuation;   
			return (ambient + (1.0 - shadow) * (diffuse + specular));
		}

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

		// TODO: Fix shadow edge shimmering, mostly visible when up close
 
		float CalculateShadows(vec3 fragPosWorldSpace)
		{
			vec4 fragPosViewSpace = u_View * vec4(fragPosWorldSpace, 1.0);
			float depthValue = abs(fragPosViewSpace.z);

			int layer = -1;
			for(int i = 0; i < u_CascadeCount; i++)
			{
				if(depthValue < u_CascadePlaneDistances[i])
				{
					layer = i;
					break;
				}
			}

			if(layer == -1 || layer >= u_CascadeCount)
			{
				layer = u_CascadeCount - 1;
			}

			vec4 fragPosLightSpace = LighSpaceMatrices[layer] * vec4(fragPosWorldSpace, 1.0);
			vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
			projCoords.xy = projCoords.xy * 0.5 + 0.5;
			float currentDepth = projCoords.z;
			
			if(currentDepth > 1.0)
			{
				return 0.0;
			}

			vec3 normal = normalize(Normal);
			vec3 lightDir = normalize(-u_DirectionalLight.direction);
			float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
			const float biasModifier = 0.5f;
			float currentDistance = (layer < u_CascadeCount) ? u_CascadePlaneDistances[layer] : u_FarPlane;
			bias *= 1.0 / (currentDistance * biasModifier);

			float shadow = 0.0;
			vec2 texelSize = 1.0 / vec2(textureSize(u_ShadowMap, 0));
			float filterRadius = 1.5 * (1.0 / float(layer + 1));
			float angle = randomAngle(fragPosWorldSpace);
			mat2 rot = mat2(cos(angle), -sin(angle), sin(angle), cos(angle));
			for(int i = 0; i < 16; i++)
			{
				vec2 offset = rot * POISSON_DISK[i] * texelSize * filterRadius;
				float pcfDepth = texture(u_ShadowMap, vec3(projCoords.xy + offset, layer)).r;
				shadow += (currentDepth - bias) > pcfDepth ? 1.0 : 0.0;
			}
			
			return shadow / 9.0;
		}

		void main()
		{
			// debug only
			vec4 fragPosViewSpace = u_View * vec4(FragPos, 1.0);
			float depthValue = abs(fragPosViewSpace.z);

			int layer = -1;
			for(int i = 0; i < u_CascadeCount; i++)
			{
				if(depthValue < u_CascadePlaneDistances[i])
				{
					layer = i;
					break;
				}
			}

			if(layer == -1 || layer >= u_CascadeCount)
			{
				layer = u_CascadeCount - 1;
			}
			
			vec3 cascadeColors[4] = vec3[](
			vec3(1.0, 0.0, 0.0), // Red   = Layer 0 (Closest)
			vec3(0.0, 1.0, 0.0), // Green = Layer 1
			vec3(0.0, 0.0, 1.0), // Blue  = Layer 2
			vec3(1.0, 1.0, 0.0)  // Yellow= Layer 3 (Farthest)
			);
			// debug only

			vec3 normal;
			vec3 sampledNormal = texture(u_Material.normal, TexCoords).rgb;
			normal = normalize(sampledNormal * 2.0 - 1.0);
			//normal.x = -normal.x;
			//normal.y = -normal.y;
			vec3 worldNormal = normalize(TBN * normal);
			vec3 viewDir = normalize(u_ViewPos - FragPos);
			float shadow = CalculateShadows(FragPos);
			vec3 result = CalculateDirectionalLight(u_DirectionalLight, viewDir, worldNormal, shadow);
			//result += CalculatePointLight(u_PointLight, norm, FragPos, viewDir, shadow);
			FragColor = vec4(result, 1.0);
		}
	)";

	inline constexpr const char* LightVertex = R"(#version 460 core

		layout (location = 0) in vec3 aPos;

		uniform mat4 u_ViewProjection;
		uniform mat4 u_Model;

		void main()
		{
			gl_Position = u_ViewProjection * u_Model * vec4(aPos, 1.0);
		}
	)";

	inline constexpr const char* LightFragment = R"(#version 440 core

		out vec4 FragColor;

		void main()
		{
			FragColor = vec4(1.0);
		}
	)";
	
	inline constexpr const char* GridVertexShader = R"(#version 460 core
		
		layout(location = 0) in vec3 aPos;

		const float gridSize = 100.0;
			
		uniform mat4 u_ViewProjection;
		uniform mat4 u_Model;
		uniform vec3 u_CamPos;
		uniform float u_CellSize;
		out vec2 coords;
		out vec3 camPos;
		out float cellSize;

		void main() 
		{	
			vec4 worldPos = vec4(aPos, 1.0);
			worldPos.xyz *= gridSize;
			worldPos.xz += u_CamPos.xz;

			gl_Position = u_ViewProjection * u_Model * worldPos;
			coords = worldPos.xz;
			camPos = u_CamPos;
			cellSize = u_CellSize;
		}
	)";

	inline constexpr const char* GridFragmentShader = R"(#version 460 core
		
		in vec2 coords;
		in vec3 camPos;
		in float cellSize;
		out vec4 FragColor;

		const float gridSize = 100.0;

		float subcellSize = cellSize * 0.1;

		const vec3 subGridColor = vec3(0.3, 0.3, 0.3);
		const vec3 mainGridColor = vec3(0.55, 0.55, 0.55);

		const float maxFadeDistance = 25.0;

		void main() 
		{		
			float camDist = length(coords - camPos.xz);
			float opacityFalloff = smoothstep(1.0, 0.0, camDist / maxFadeDistance);

			vec2 cellUV = mod(coords, cellSize);
			vec2 subUV = mod(cellUV, subcellSize);

			float mainGridThickness = cellSize * 0.008;
			float subGridThickness = cellSize * 0.003;

			float mainLineX = step(cellUV.x, mainGridThickness) + step(cellSize - mainGridThickness, cellUV.x);
			float mainLineY = step(cellUV.y, mainGridThickness) + step(cellSize - mainGridThickness, cellUV.y);
			float isMainGrid = clamp(mainLineX + mainLineY, 0.0, 1.0);
	
			float subLineX = step(subUV.x, subGridThickness) + step(subcellSize - subGridThickness, subUV.x);
			float subLineY = step(subUV.y, subGridThickness) + step(subcellSize - subGridThickness, subUV.y);
			float isSubGrid = clamp(subLineX + subLineY, 0.0, 1.0);

			vec3 gridRGB = mix(subGridColor, mainGridColor, isMainGrid);
			float gridAlpha = clamp(isMainGrid + isSubGrid, 0.0, 0.2);
			
			FragColor = vec4(gridRGB * opacityFalloff, gridAlpha);
		}
	)";

	inline constexpr const char* SkyboxVertexShader = R"(#version 460 core
			
		layout(location = 0) in vec3 aPos;

		out vec3 TexCoords;

		uniform mat4 u_ViewProjection;

		void main()
		{
			TexCoords = aPos;
			vec4 pos = u_ViewProjection * vec4(aPos, 1.0);
			gl_Position = vec4(pos.xy, 0.0, pos.w);
		}
	)";

	inline constexpr const char* SkyboxFragmentShader = R"(#version 460 core
			
		out vec4 FragColor;

		in vec3 TexCoords;

		uniform samplerCube u_SkyboxTex;

		void main()
		{
			FragColor = texture(u_SkyboxTex, TexCoords);
		}
	)";
}

/*for(int x = -1; x <= 1; x++)
			{
				for(int y = -1; y <= 1; y++)
				{
					float pcfDepth = texture(u_ShadowMap, vec3(projCoords.xy + vec2(x, y) * texelSize, layer)).r;
					shadow += (currentDepth - bias) > pcfDepth ? 1.0 : 0.0;
				}
			}
			shadow /= 9.0;*/