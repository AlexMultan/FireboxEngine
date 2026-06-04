#include "OpenGLVertexBuffer.h"
#include "Engine/Utils/OpenGLDebugger.h"
#include "Engine/Utils/Assert.h"

#include <SDL3/SDL.h>
#include <glad/glad.h>

Firebox::OpenGLVertexBuffer::OpenGLVertexBuffer(uint size)
{
	ASSERT(sizeof(uint32_t) == sizeof(GLuint), "Size in bytes of uint32_t doesn't match the size of GLuint!");
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
	glCheckError();
}

Firebox::OpenGLVertexBuffer::OpenGLVertexBuffer(const void* data, uint size)
{
	ASSERT(sizeof(uint32_t) == sizeof(GLuint), "Size in bytes of uint32_t doesn't match the size of GLuint!");
	while (glGetError() != GL_NO_ERROR);
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
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
	glCheckError();
}

void Firebox::OpenGLVertexBuffer::SetBufferData(const void* data, uint size)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	glCheckError();
}
