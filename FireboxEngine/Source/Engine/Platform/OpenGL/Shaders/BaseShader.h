#pragma once

namespace Firebox::Shaders::GLSL {

	inline constexpr const char* BaseVertex = R"(#version 440 core

		layout (location = 0) in vec3 aPos;
		layout (location = 1) in vec3 aNormal;
		layout (location = 2) in vec2 aTexCoords;

		uniform mat4 u_ViewProjection;
		uniform mat4 u_Model;
		uniform mat3 u_InverseNormal;

		out vec3 FragPos;
		out vec3 Normal;
		out vec2 TexCoords;

		void main()
		{
			FragPos = vec3(u_Model * vec4(aPos, 1.0));
			Normal = u_InverseNormal * aNormal;
			TexCoords = aTexCoords;
			gl_Position = u_ViewProjection * u_Model * vec4(aPos, 1.0);
		}
	)";

	inline constexpr const char* BaseFragment = R"(#version 440 core

		out vec4 FragColor;

		struct Material {
			vec3 ambient;
			sampler2D diffuse;
			sampler2D specular;
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
		in vec3 Normal;
		in vec2 TexCoords;
		
		uniform Material u_Material;
		uniform DirectionalLight u_DirectionalLight; 
		uniform PointLight u_PointLight; 
		uniform vec3 u_ViewPos;

		vec3 CalculateDirectionalLight(DirectionalLight directionalLight, vec3 normal, vec3 viewDir)
		{
			vec3 directionalLightDir = normalize(-directionalLight.direction);
			float diff = max(dot(normal, directionalLightDir), 0.0);
			vec3 reflectDir = reflect(-directionalLightDir, normal);
			float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
			vec3 ambient = directionalLight.ambient * texture(u_Material.diffuse, TexCoords).rgb;
			vec3 diffuse = directionalLight.diffuse * diff * texture(u_Material.diffuse, TexCoords).rgb;
			vec3 specular = directionalLight.specular * spec * texture(u_Material.specular, TexCoords).rgb;
			return (ambient + diffuse + specular);
		}

		vec3 CalculatePointLight(PointLight pointLight, vec3 normal, vec3 fragPos, vec3 viewDir)
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
			return (ambient + diffuse + specular);
		}

		void main()
		{
			vec3 norm = normalize(Normal);
			vec3 viewDir = normalize(u_ViewPos - FragPos);
			vec3 result = CalculateDirectionalLight(u_DirectionalLight, norm, viewDir);
			//result += CalculatePointLight(u_PointLight, norm, FragPos, viewDir);
			FragColor = vec4(result, 1.0);
		}
	)";

	inline constexpr const char* LightVertex = R"(#version 440 core

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

	inline constexpr const char* GridVertexShader = R"(#version 440 core
		
		layout(location = 0) in vec3 aPos;

		const float gridSize = 100.0;
			
		uniform mat4 u_ViewProjection;
		uniform mat4 u_Model;
		uniform vec3 u_CamPos;
		out vec2 coords;
		out vec3 camPos;

		void main() 
		{	
			vec4 worldPos = vec4(aPos, 1.0);
			worldPos.xyz *= gridSize;
			worldPos.xz += u_CamPos.xz;

			gl_Position = u_ViewProjection * u_Model * worldPos;
			coords = worldPos.xz;
			camPos = u_CamPos;
		}
	)";

	inline constexpr const char* GridFragmentShader = R"(#version 440 core
		
		in vec2 coords;
		in vec3 camPos;
		out vec4 FragColor;

		const float gridSize = 100.0;
		const float cellSize = 2.0;
		const float halfCellSize = cellSize * 0.5;

		const float subcellSize = 0.1;
		const float halfSubcellSize = subcellSize * 0.5;	

		const vec3 subGridColor = vec3(0.3, 0.3, 0.3);
		const vec3 mainGridColor = vec3(0.55, 0.55, 0.55);

		const float maxFadeDistance = 25.0;

		void main() 
		{		
			float camDist = length(coords - camPos.xz);
			float opacityFalloff = smoothstep(1.0, 0.0, camDist / maxFadeDistance);

			vec2 cellUV = mod(coords, cellSize);
			vec2 subUV = mod(cellUV, subcellSize);

			float mainGridThickness = 0.01;
			float subGridThickness = 0.002;

			float mainLineX = step(cellUV.x, mainGridThickness) + step(cellSize - mainGridThickness, cellUV.x);
			float mainLineY = step(cellUV.y, mainGridThickness) + step(cellSize - mainGridThickness, cellUV.y);
			float isMainGrid = clamp(mainLineX + mainLineY, 0.0, 1.0);
	
			float subLineX = step(subUV.x, subGridThickness) + step(subcellSize - subGridThickness, subUV.x);
			float subLineY = step(subUV.y, subGridThickness) + step(subcellSize - subGridThickness, subUV.y);
			float isSubGrid = clamp(subLineX + subLineY, 0.0, 1.0);

			vec3 gridRGB = mix(subGridColor, mainGridColor, isMainGrid);
			float gridAlpha = clamp(isMainGrid + isSubGrid, 0.0, 1.0);
			
			FragColor = vec4(gridRGB * opacityFalloff, gridAlpha);
		}
	)";
}