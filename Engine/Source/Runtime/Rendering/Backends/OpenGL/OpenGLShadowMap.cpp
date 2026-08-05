#include "OpenGLShadowMap.h"
#include "Core/Log.h"
#include "OpenGLDebugger.h"

#include <glad/glad.h>

#define NUM_SHADOW_CASCADE_LAYERS 5

Firebox::OpenGL::OpenGLShadowMap::OpenGLShadowMap(uint resolution)
{
	FB_CORE_TRACE("Depth Map Resolution:{0}", m_DepthMapResolution);
	Invalidate();
}

Firebox::OpenGL::OpenGLShadowMap::~OpenGLShadowMap()
{
	glDeleteFramebuffers(1, &m_LightFBO);
	glDeleteTextures(1, &m_LightDepthMaps);
}

void Firebox::OpenGL::OpenGLShadowMap::BindShadowMap()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_LightFBO);
	glViewport(0, 0, m_DepthMapResolution, m_DepthMapResolution);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void Firebox::OpenGL::OpenGLShadowMap::UnbindShadowMap()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Firebox::OpenGL::OpenGLShadowMap::ResizeFramebuffer(uint resolution)
{
	m_DepthMapResolution = resolution;
	Invalidate();
}

uint Firebox::OpenGL::OpenGLShadowMap::GetDepthTexture() const
{
	return m_LightDepthMaps;
}
void Firebox::OpenGL::OpenGLShadowMap::Invalidate()
{
	if (m_LightFBO)
	{
		glDeleteFramebuffers(1, &m_LightFBO);
		glDeleteTextures(1, &m_LightDepthMaps);
	}
	glGenFramebuffers(1, &m_LightFBO);

	glGenTextures(1, &m_LightDepthMaps);
	glBindTexture(GL_TEXTURE_2D_ARRAY, m_LightDepthMaps);
	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_DEPTH_COMPONENT32F, m_DepthMapResolution, m_DepthMapResolution, NUM_SHADOW_CASCADE_LAYERS, 0,
		GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	constexpr float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BORDER_COLOR, borderColor);

	glBindFramebuffer(GL_FRAMEBUFFER, m_LightFBO);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_LightDepthMaps, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		FB_CORE_ERROR("Shadow map framebuffer is not complete!");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
