#include "OpenGLIndexBuffer.h"
#include "Engine/Utils/OpenGLDebugger.h"
#include "Engine/Utils/Assert.h"

#include <glad/glad.h>

Firebox::OpenGLIndexBuffer::OpenGLIndexBuffer(const uint* indices, uint count) : m_Count(count)
{
	FB_ASSERT(sizeof(uint32_t) == sizeof(GLuint), "Size in bytes of uint32_t doesn't match the size of GLuint!");
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	glCheckError();
}

Firebox::OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
	glCheckError();
}

void Firebox::OpenGLIndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glCheckError();
}

void Firebox::OpenGLIndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glCheckError();
}
