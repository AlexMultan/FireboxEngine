#include "Engine/Rendering/Resources/Shader.h"
#include "Engine/Platform/OpenGL/OpenGLShader.h"

Scope<Firebox::Shader> Firebox::Shader::Create(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	return CreateScope<OpenGLShader>(vertexShaderPath, fragmentShaderPath, false);
}

Scope<Firebox::Shader> Firebox::Shader::CreateFromSource(const char* vertexSrc, const char* fragmentSrc)
{
	return CreateScope<OpenGLShader>(vertexSrc, fragmentSrc, true);
}
