#pragma once

namespace Firebox::Shaders::GLSL {

	inline constexpr const char* DepthVertex = R"(#version 460 core

		layout (location = 0) in vec3 aPos;

		uniform mat4 u_ViewProjection;
		uniform mat4 u_Model;

		void main()
		{
			gl_Position = u_ViewProjection * u_Model * vec4(aPos, 1.0);
		}
	)";

	inline constexpr const char* DepthFragment = R"(#version 440 core

		out vec4 FragColor;

		uniform float u_Near;
		uniform float u_Far;

		float LinearizeDepth(float depth)
		{
			return (u_Near * u_Far) / (depth * (u_Far - u_Near) + u_Near);
		}

		void main()
		{
			float linearDepth = LinearizeDepth(gl_FragCoord.z);
			float normalized = log(linearDepth + 1.0) / log(u_Far + 1.0);
			FragColor = vec4(vec3(normalized), 1.0);
		}
	)";

	inline constexpr const char* ShadowMapDepthVertex = R"(#version 460 core

		layout (location = 0) in vec3 aPos;

		uniform mat4 u_LightSpaceMatrix;
		uniform mat4 u_Model;

		void main()
		{
			gl_Position = u_LightSpaceMatrix * u_Model * vec4(aPos, 1.0);
		}
	)";

	inline constexpr const char* ShadowMapDepthFragment = R"(#version 440 core

		void main()
		{
	
		}
	)";
}