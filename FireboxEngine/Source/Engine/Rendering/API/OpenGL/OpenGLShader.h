#pragma once

#include "Engine/Core/Core.h"

namespace Firebox {

	class FIREBOX_API OpenGLShader
	{
	public:
		uint ID;

		OpenGLShader();
		OpenGLShader(const char* vertexShaderPath, const char* fragmentShaderPath);
		~OpenGLShader();

		void UseShader();
		void SetFloat4(const String& name, float r, float g, float b, float a);
	};
}