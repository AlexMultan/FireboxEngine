#include "OpenGLFramebuffer.h"
#include "Core/Log.h"
#include "Utils/OpenGLDebugger.h"

#include <glad/glad.h>

Firebox::OpenGL::OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& specs) : m_Specs(specs)
{
	Invalidate();
}

Firebox::OpenGL::OpenGLFramebuffer::~OpenGLFramebuffer()
{
	glDeleteFramebuffers(1, &m_FBO);
	glDeleteRenderbuffers(1, &m_RBO);
	glDeleteTextures(1, &m_ColorAttachment);
}

void Firebox::OpenGL::OpenGLFramebuffer::BindFramebuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
	glViewport(0, 0, m_Specs.Width, m_Specs.Height);
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT || GL_DEPTH_BUFFER_BIT);
}

void Firebox::OpenGL::OpenGLFramebuffer::UnbindFramebuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Firebox::OpenGL::OpenGLFramebuffer::ResizeFramebuffer(uint width, uint height)
{
	m_Specs.Width = width;
	m_Specs.Height = height;
	Invalidate();
}

void Firebox::OpenGL::OpenGLFramebuffer::ClearFramebuffer()
{
	
}

void Firebox::OpenGL::OpenGLFramebuffer::Invalidate()
{
	if (m_FBO)
	{
		glDeleteFramebuffers(1, &m_FBO);
		glDeleteTextures(1, &m_ColorAttachment);
		glDeleteRenderbuffers(1, &m_RBO);
	}

	glGenTextures(1, &m_ColorAttachment);
	glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Specs.Width, m_Specs.Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenFramebuffers(1, &m_FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

	glGenRenderbuffers(1, &m_RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH32F_STENCIL8, m_Specs.Width, m_Specs.Height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		FB_CORE_ERROR("Framebuffer is not complete!");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
