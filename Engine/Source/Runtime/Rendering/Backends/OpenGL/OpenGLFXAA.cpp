#include "OpenGLFXAA.h"
#include "Core/Log.h"

#include <glad/glad.h>

Firebox::OpenGL::OpenGLFXAA::OpenGLFXAA()
{
}

Firebox::OpenGL::OpenGLFXAA::~OpenGLFXAA()
{
	if (m_FXAAColorBuffer)
		glDeleteTextures(1, &m_FXAAColorBuffer);
	if (m_FXAA_FBO)
		glDeleteFramebuffers(1, &m_FXAA_FBO);
}

void Firebox::OpenGL::OpenGLFXAA::BindFXAABuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_FXAA_FBO);
}

void Firebox::OpenGL::OpenGLFXAA::UnbindFXAABuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Firebox::OpenGL::OpenGLFXAA::ResizeFXAABuffer(uint width, uint height)
{
	if (width == 0 || height == 0)
		return;

	if (m_FXAA_FBO && m_FXAAInfo.Width == width && m_FXAAInfo.Height == height)
		return;

	m_FXAAInfo.Width = width;
	m_FXAAInfo.Height = height;
	Invalidate();
}

void Firebox::OpenGL::OpenGLFXAA::BindSceneTexture(uint textureID, uint textureUnit)
{
	glBindTextureUnit(textureUnit, textureID);
}

void Firebox::OpenGL::OpenGLFXAA::BlitToFramebuffer(uint destinationFramebufferID)
{
	glBlitNamedFramebuffer(m_FXAA_FBO, destinationFramebufferID, 0, 0, m_FXAAInfo.Width, m_FXAAInfo.Height, 0, 0, m_FXAAInfo.Width, 
		m_FXAAInfo.Height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

uint Firebox::OpenGL::OpenGLFXAA::GetFXAAColorBuffer()
{
	if (m_FXAAColorBuffer >= 0)
		return m_FXAAColorBuffer;
}

void Firebox::OpenGL::OpenGLFXAA::Invalidate()
{
	if (m_FXAAColorBuffer)
	{
		glDeleteTextures(1, &m_FXAAColorBuffer);
		m_FXAAColorBuffer = 0;
	}
	if (m_FXAA_FBO)
	{
		glDeleteFramebuffers(1, &m_FXAA_FBO);
		m_FXAA_FBO = 0;
	}

	glGenFramebuffers(1, &m_FXAA_FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FXAA_FBO);

	glGenTextures(1, &m_FXAAColorBuffer);
	glBindTexture(GL_TEXTURE_2D, m_FXAAColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_FXAAInfo.Width, m_FXAAInfo.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_FXAAColorBuffer, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) 
		FB_CORE_ERROR("FXAA Framebuffer is not complete!");

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
