#include "OpenGLShadowMap.h"
#include "Engine/Core/Log.h"
#include "Engine/Utils/OpenGLDebugger.h"

#include <glad/glad.h>

Firebox::OpenGL::OpenGLShadowMap::OpenGLShadowMap(uint width, uint height) : m_Width(width), m_Height(height)
{
	Invalidate();
}

Firebox::OpenGL::OpenGLShadowMap::~OpenGLShadowMap()
{
	glDeleteFramebuffers(1, &m_DepthMapFBO);
	glDeleteTextures(1, &m_DepthMap);
}

void Firebox::OpenGL::OpenGLShadowMap::BindFramebuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_DepthMapFBO);
	glViewport(0, 0, m_Width, m_Height);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void Firebox::OpenGL::OpenGLShadowMap::UnbindFramebuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Firebox::OpenGL::OpenGLShadowMap::ResizeFramebuffer(uint width, uint height)
{
	m_Width = width;
	m_Height = height;
	Invalidate();
}

uint Firebox::OpenGL::OpenGLShadowMap::GetDepthTexture() const
{
	return m_DepthMap;
}

void Firebox::OpenGL::OpenGLShadowMap::Invalidate()
{
	if (m_DepthMapFBO)
	{
		glDeleteFramebuffers(1, &m_DepthMapFBO);
		glDeleteTextures(1, &m_DepthMap);
	}

	glGenTextures(1, &m_DepthMap);
	glBindTexture(GL_TEXTURE_2D, m_DepthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_Width, m_Height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glGenFramebuffers(1, &m_DepthMapFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_DepthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		FB_CORE_ERROR("Shadow map framebuffer is not complete!");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
