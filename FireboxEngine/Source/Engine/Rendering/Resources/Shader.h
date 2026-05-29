#pragma once

#include "Engine/Core/Core.h"
#include "Engine/Utils/Types.h"

namespace Firebox {

	class FIREBOX_API Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void UseShader() = 0;
		virtual void SetFloat4(const String& name, float r, float g, float b, float a) = 0;
		virtual void SetMat4(const String& name, const Mat4& matrix) = 0;

		virtual uint64 GetID() const = 0;

		static Scope<Shader> Create(const char* vertexShaderPath, const char* fragmentShaderPath);
		static Scope<Shader> CreateFromSource(const char* vertexSrc, const char* fragmentSrc);

	};
}