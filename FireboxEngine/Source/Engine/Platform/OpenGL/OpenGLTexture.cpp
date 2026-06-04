#include "OpenGLTexture.h"
#include "Engine/Core/Log.h"
#include "Engine/Utils/OpenGLDebugger.h"

#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <filesystem>

Firebox::OpenGLTexture::OpenGLTexture(const String& path)
{
	glGenTextures(1, &m_TextureID);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	FIREBOX_CORE_TRACE(path.c_str());

	if (data)
	{
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		FIREBOX_CORE_INFO("Width: {0}, Height: {1}, Channels: {2}", width, height, nrChannels);
		FIREBOX_CORE_INFO("Data ptr: {0}", (void*)data);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		FIREBOX_CORE_ERROR("STB reason: {0}", stbi_failure_reason());
		FIREBOX_CORE_ERROR("Failed to load texture!");
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
}

Firebox::OpenGLTexture::~OpenGLTexture()
{

}

void Firebox::OpenGLTexture::BindTexture(uint slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void Firebox::OpenGLTexture::UnbindTexture()
{
	//glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Firebox::OpenGLTexture::DeleteTexture()
{
	glDeleteTextures(1, &m_TextureID);
}