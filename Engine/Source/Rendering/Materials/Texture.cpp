#include "Texture.h"
#include "Rendering/Backends/OpenGL/OpenGLTexture.h"


Ref<Firebox::Texture> Firebox::Texture::Create(const String& path)
{
	Ref<Texture> texture = CreateRef<OpenGLTexture>(path);
	texture->SetTexturePath(path);
	return texture;
}

Ref<Firebox::Texture> Firebox::Texture::CreateCubemap(const DynamicArray<String>& faces)
{
	return CreateRef<OpenGLTexture>(faces);
}

void Firebox::Texture::SetTexturePath(const String& path)
{
	m_TexturePath = path;
}
