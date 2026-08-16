#include "OpenGLSSAO.h"
#include "Core/Log.h"

#include <glad/glad.h>

Firebox::OpenGL::OpenGLSSAO::OpenGLSSAO()
{
}

Firebox::OpenGL::OpenGLSSAO::~OpenGLSSAO()
{
}

void Firebox::OpenGL::OpenGLSSAO::BindSSAOBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_SSAO_FBO);
}

void Firebox::OpenGL::OpenGLSSAO::UnbindSSAOBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Firebox::OpenGL::OpenGLSSAO::BindSSAOBlurBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_SSAOBlurFBO);
}

void Firebox::OpenGL::OpenGLSSAO::UnbindSSAOBlurBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Firebox::OpenGL::OpenGLSSAO::ResizeSSAOBuffer(uint width, uint height)
{
	m_SSAOInfo.Width = width;
	m_SSAOInfo.Height = height;
	Invalidate();
}

void Firebox::OpenGL::OpenGLSSAO::GenerateNoiseTexture()
{
	SSAO::GenerateNoiseTexture();

	glGenTextures(1, &m_NoiseTexture);
	glBindTexture(GL_TEXTURE_2D, m_NoiseTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, 4, 4, 0, GL_RGB, GL_FLOAT, &m_SSAONoise[0]);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void Firebox::OpenGL::OpenGLSSAO::BindNoiseTexture()
{
	glActiveTexture(GL_TEXTURE26);
	glBindTexture(GL_TEXTURE_2D, m_NoiseTexture);
}

void Firebox::OpenGL::OpenGLSSAO::BindSSAOTexture()
{
	glActiveTexture(GL_TEXTURE25);
	glBindTexture(GL_TEXTURE_2D, m_SSAOColorBuffer);
}

void Firebox::OpenGL::OpenGLSSAO::BindSSAOBlurTexture()
{
	glActiveTexture(GL_TEXTURE24);
	glBindTexture(GL_TEXTURE_2D, m_SSAOColorBufferBlur);
}

void Firebox::OpenGL::OpenGLSSAO::Invalidate()
{
	if (m_SSAO_FBO)
	{
		glDeleteFramebuffers(1, &m_SSAO_FBO);
		glDeleteFramebuffers(1, &m_SSAOBlurFBO);
		glDeleteTextures(1, &m_SSAOColorBuffer);
	}

	glGenFramebuffers(1, &m_SSAO_FBO);
	glGenFramebuffers(1, &m_SSAOBlurFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_SSAO_FBO);

	glGenTextures(1, &m_SSAOColorBuffer);
	glBindTexture(GL_TEXTURE_2D, m_SSAOColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_SSAOInfo.Width, m_SSAOInfo.Height, 0, GL_RED, GL_FLOAT, NULL);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_SSAOColorBuffer, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		FB_CORE_ERROR("SSAO Framebuffer is not complete!");

	glBindFramebuffer(GL_FRAMEBUFFER, m_SSAOBlurFBO);
	glGenTextures(1, &m_SSAOColorBufferBlur);
	glBindTexture(GL_TEXTURE_2D, m_SSAOColorBufferBlur);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_SSAOInfo.Width, m_SSAOInfo.Height, 0, GL_RED, GL_FLOAT, NULL);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_SSAOColorBufferBlur, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		FB_CORE_ERROR("SSAO Blur Framebuffer is not complete!");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
