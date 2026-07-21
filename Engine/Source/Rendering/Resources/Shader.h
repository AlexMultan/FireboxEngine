#pragma once

#include "Core/Core.h"

namespace Firebox {

	class FIREBOX_API Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void UseShader() = 0;
		virtual void SetFloat(const String& name, float value) = 0;
		virtual void SetInt(const String& name, int value) = 0;
		virtual void SetVector3(const String& name, Vector3 vector3) = 0;
		virtual void SetVector4(const String& name, Vector4 vector4) = 0;
		virtual void SetMat3(const String& name, const Mat3& matrix) = 0;
		virtual void SetMat4(const String& name, const Mat4& matrix) = 0;

		virtual uint GetID() const = 0;

		static Ref<Shader> Create(const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryShaderPath);
		static Ref<Shader> CreateFromSource(const char* vertexSrc, const char* fragmentSrc, const char* geometrySrc);

	};
}