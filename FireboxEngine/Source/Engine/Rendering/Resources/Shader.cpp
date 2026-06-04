#include "Engine/Rendering/Resources/Shader.h"
#include "Engine/Platform/OpenGL/OpenGLShader.h"

Ref<Firebox::Shader> Firebox::Shader::Create(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	return CreateRef<OpenGLShader>(vertexShaderPath, fragmentShaderPath, false);
}

Ref<Firebox::Shader> Firebox::Shader::CreateFromSource(const char* vertexSrc, const char* fragmentSrc)
{
	return CreateRef<OpenGLShader>(vertexSrc, fragmentSrc, true);
}
