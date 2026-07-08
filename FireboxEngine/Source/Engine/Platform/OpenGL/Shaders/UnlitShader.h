#pragma once

namespace Firebox::Shaders::GLSL {

	inline constexpr const char* UnlitVertex = R"(#version 460 core

		layout (location = 0) in vec3 aPos;
		layout (location = 2) in vec2 aTexCoords;

		uniform mat4 u_ViewProjection;
		uniform mat4 u_Model;
		uniform float u_Tiling;

		out vec2 TexCoords;

		void main()
		{
			TexCoords = aTexCoords * u_Tiling;
			gl_Position = u_ViewProjection * u_Model * vec4(aPos, 1.0);
		}
	)";

	inline constexpr const char* UnlitFragment = R"(#version 460 core

		out vec4 FragColor;

		uniform sampler2D u_Diffuse;

		in vec2 TexCoords;

		void main()
		{
			FragColor = vec4(texture(u_Diffuse, TexCoords));
		}
	)";
}