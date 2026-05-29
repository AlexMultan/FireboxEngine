#pragma once

namespace Firebox::Shaders::OpenGL {

	inline constexpr const char* BaseVertex = R"(#version 440 core

		layout (location = 0) in vec3 aPos;
		layout (location = 1) in vec2 aTexCoord;

		out vec2 o_TexCoord;

		uniform mat4 u_ViewProjection;
		uniform mat4 u_Model;

		void main()
		{
			gl_Position = u_ViewProjection * u_Model * vec4(aPos, 1.0);
			o_TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
		}
	)";

	inline constexpr const char* BaseFragment = R"(#version 440 core

		out vec4 FragColor;
		in vec2 o_TexCoord;
		uniform sampler2D u_Texture;

		void main()
		{
			FragColor = texture(u_Texture, o_TexCoord);
		}
	)";
}