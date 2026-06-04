#include "Texture.h"
#include "Engine/Platform/OpenGL/OpenGLTexture.h"

Scope<Firebox::Texture> Firebox::Texture::Create(const String& path)
{
	return CreateScope<OpenGLTexture>(path);
}
