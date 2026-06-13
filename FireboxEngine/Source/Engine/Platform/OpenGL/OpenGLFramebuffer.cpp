#include "OpenGLFramebuffer.h"
#include "Engine/Core/Log.h"
#include "Engine/Utils/OpenGLDebugger.h"

#include <glad/glad.h>

Firebox::OpenGL::OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& specs) : m_Specs(specs)
{
	Invalidate();
}

Firebox::OpenGL::OpenGLFramebuffer::~OpenGLFramebuffer()
{
	glDeleteFramebuffers(1, &m_FBO);
	glDeleteFramebuffers(1, &m_MsFBO);
	glDeleteRenderbuffers(1, &m_RBO);
	glDeleteTextures(1, &m_ColorAttachment);
	glDeleteTextures(1, &m_MsColorTex);
}

void Firebox::OpenGL::OpenGLFramebuffer::BindFramebuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_MsFBO);
	glViewport(0, 0, m_Specs.Width, m_Specs.Height);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT || GL_DEPTH_BUFFER_BIT);

	glEnable(GL_MULTISAMPLE);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_MsFBO);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_FBO);

	glBlitFramebuffer(0, 0, m_Specs.Width, m_Specs.Height, 0, 0, m_Specs.Width, m_Specs.Height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
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

	if (m_MsFBO)
	{
		glDeleteFramebuffers(1, &m_MsFBO);
		glDeleteTextures(1, &m_MsColorTex);
	}

	glGenTextures(1, &m_MsColorTex);
	glBindTexture(GL_TEXTURE_2D, m_MsColorTex);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, m_Specs.Width, m_Specs.Height, GL_TRUE);
	glCheckError();

	glGenFramebuffers(1, &m_MsFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_MsFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_MsColorTex, 0);
	glCheckError();

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		FIREBOX_CORE_ERROR("Multisample Framebuffer is not complete");


	glGenTextures(1, &m_ColorAttachment);
	glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Specs.Width, m_Specs.Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glCheckError();

	glGenFramebuffers(1, &m_FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
	glCheckError();

	glGenRenderbuffers(1, &m_RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Specs.Width, m_Specs.Height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);
	glCheckError();

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);
	glCheckError();

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		FIREBOX_CORE_ERROR("Framebuffer is not complete!");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
