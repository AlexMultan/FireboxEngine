#pragma once

#include "Engine/Rendering/Resources/Shader.h"

namespace Firebox {

	class FIREBOX_API OpenGLShader : public Shader
	{
	public:
		uint ID;

		OpenGLShader();
		OpenGLShader(const char* vertexSrc, const char* fragmentSrc, bool fromSource);
		~OpenGLShader();

		void Compile(const char* vertexShader, const char* fragmentShader);
		virtual void UseShader() override;
		virtual void SetFloat4(const String& name, float r, float g, float b, float a) override;
		virtual void SetMat4(const String& name, const Mat4& matrix) override;

		virtual uint64 GetID() const override { return ID; }
	};
}