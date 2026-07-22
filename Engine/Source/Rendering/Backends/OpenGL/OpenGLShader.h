#pragma once

#include "Rendering/Materials/Shader.h"

namespace Firebox {

	class FIREBOX_API OpenGLShader : public Shader
	{
	public:
		OpenGLShader();
		OpenGLShader(const char* vertexSrc, const char* fragmentSrc, const char* geomatrySrc, bool fromSource);
		~OpenGLShader();

		void Compile(const char* vertexShader, const char* fragmentShader, const char* geomatryShader);
		virtual void UseShader() override;
		virtual void SetFloat(const String& name, float value) override;
		virtual void SetInt(const String& name, int value) override;
		virtual void SetVector3(const String& name, Vector3 vector3) override;
		virtual void SetVector4(const String& name, Vector4 vector4) override;
		virtual void SetMat3(const String& name, const Mat3& matrix) override;
		virtual void SetMat4(const String& name, const Mat4& matrix) override;

		virtual uint GetID() const override { return ID; }

	private:
		uint64 ID;
	};
}