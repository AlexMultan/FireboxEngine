#include "Texture.h"
#include "Engine/Platform/OpenGL/OpenGLTexture.h"

Ref<Firebox::Texture> Firebox::Texture::Create(const String& path)
{
	return CreateRef<OpenGLTexture>(path);
}
