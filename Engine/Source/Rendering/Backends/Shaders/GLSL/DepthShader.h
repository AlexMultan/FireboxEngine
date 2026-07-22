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

	inline constexpr const char* DepthFragment = R"(#version 460 core

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

		uniform mat4 u_Model;

		void main()
		{
			gl_Position = u_Model * vec4(aPos, 1.0);
		}
	)";

	inline constexpr const char* ShadowMapDepthFragment = R"(#version 460 core

		void main()
		{
			
		}
	)";

	inline constexpr const char* ShadowMapDepthGeometry = R"(#version 460 core

		layout(triangles, invocations = 5) in;
		layout(triangle_strip, max_vertices = 3) out;

		layout(std140, binding = 0) uniform LightSpaceMatrices
		{
			mat4 lightSpaceMatrices[16];
		};

		void main()
		{
			for(int i = 0; i < 3; i++)
			{
				gl_Position = lightSpaceMatrices[gl_InvocationID] * gl_in[i].gl_Position;
				gl_Layer = gl_InvocationID;
				EmitVertex();
			}
			EndPrimitive();
		}
	)";
}