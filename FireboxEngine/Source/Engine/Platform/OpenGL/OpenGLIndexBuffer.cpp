#include "OpenGLIndexBuffer.h"
#include "Engine/Utils/OpenGLDebugger.h"
#include "Engine/Utils/Assert.h"

Firebox::OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t count, const uint32_t* data) : m_Count(count)
{
	ASSERT(sizeof(uint32_t) == sizeof(GLuint), "Size in bytes of uint32_t doesn't match the size of GLuint!");
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW);
	glCheckError();
}

Firebox::OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
	glCheckError();
}

void Firebox::OpenGLIndexBuffer::BindBuffer() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glCheckError();
}

void Firebox::OpenGLIndexBuffer::UnbindBuffer() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
