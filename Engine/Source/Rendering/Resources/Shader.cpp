#include "Rendering/Resources/Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"

Ref<Firebox::Shader> Firebox::Shader::Create(const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryShaderPath)
{
	return CreateRef<OpenGLShader>(vertexShaderPath, fragmentShaderPath, geometryShaderPath, false);
}

Ref<Firebox::Shader> Firebox::Shader::CreateFromSource(const char* vertexSrc, const char* fragmentSrc, const char* geometrySrc)
{
	return CreateRef<OpenGLShader>(vertexSrc, fragmentSrc, geometrySrc, true);
}
