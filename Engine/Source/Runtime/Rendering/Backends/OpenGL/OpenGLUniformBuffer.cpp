#include "OpenGLUniformBuffer.h"

#include <glad/glad.h>

Firebox::OpenGL::OpenGLUniformBuffer::OpenGLUniformBuffer()
{
	if (m_UBO)
		glDeleteBuffers(1, &m_UBO);

	glGenBuffers(1, &m_UBO);
	glBindBuffer(GL_UNIFORM_BUFFER, m_UBO);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(Mat4x4) * 16, nullptr, GL_STATIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_UBO);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

Firebox::OpenGL::OpenGLUniformBuffer::~OpenGLUniformBuffer()
{
	glDeleteBuffers(1, &m_UBO);
}

void Firebox::OpenGL::OpenGLUniformBuffer::BindUniformBuffer()
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_UBO);
}

void Firebox::OpenGL::OpenGLUniformBuffer::UnbindUniformBuffer()
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
