#include "OpenGLVertexBuffer.h"
#include "Engine/Utils/OpenGLDebugger.h"
#include "Engine/Utils/Assert.h"

Firebox::OpenGLVertexBuffer::OpenGLVertexBuffer(size_t bufferSize, const void* data)
{
	ASSERT(sizeof(uint32_t) == sizeof(GLuint), "Size in bytes of uint32_t doesn't match the size of GLuint!");
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, bufferSize, data, GL_STATIC_DRAW);
	glCheckError();
}

Firebox::OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
	glCheckError();
}

void Firebox::OpenGLVertexBuffer::BindBuffer() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glCheckError();
}

void Firebox::OpenGLVertexBuffer::UnbindBuffer() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
