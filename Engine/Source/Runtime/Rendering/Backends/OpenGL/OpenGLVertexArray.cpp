#include "OpenGLVertexArray.h"
#include "OpenGLDebugger.h"

static GLenum ShaderDataTypeToOpenGLBaseType(Firebox::ShaderDataType type)
{
	switch (type)
	{
		case Firebox::ShaderDataType::Float:    return GL_FLOAT;
		case Firebox::ShaderDataType::Float2:   return GL_FLOAT;
		case Firebox::ShaderDataType::Float3:   return GL_FLOAT;
		case Firebox::ShaderDataType::Float4:   return GL_FLOAT;
		case Firebox::ShaderDataType::Mat3:     return GL_FLOAT;
		case Firebox::ShaderDataType::Mat4:     return GL_FLOAT;
		case Firebox::ShaderDataType::Int:      return GL_INT;
		case Firebox::ShaderDataType::Int2:     return GL_INT;
		case Firebox::ShaderDataType::Int3:     return GL_INT;
		case Firebox::ShaderDataType::Int4:     return GL_INT;
		case Firebox::ShaderDataType::Bool:     return GL_BOOL;
	}
	FB_CORE_ERROR("Unknown ShaderDataType!");
	return 0;
}

Firebox::OpenGL::OpenGLVertexArray::OpenGLVertexArray()
{
	glGenVertexArrays(1, &m_RendererID);
}

Firebox::OpenGL::OpenGLVertexArray::~OpenGLVertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void Firebox::OpenGL::OpenGLVertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void Firebox::OpenGL::OpenGLVertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void Firebox::OpenGL::OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
{
	glBindVertexArray(m_RendererID);
	vertexBuffer->BindBuffer();

	const auto& layout = vertexBuffer->GetLayout();
	for(size_t i = 0; i < layout.GetElements().size(); i++)
	{
		const auto& element = layout.GetElements()[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.GetComponentCount(),
			ShaderDataTypeToOpenGLBaseType(element.Type), element.Normalized, layout.GetStride(),
			(const void*)element.Offset);
	}
	m_VertexBuffers.push_back(vertexBuffer);
}

void Firebox::OpenGL::OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
{
	glBindVertexArray(m_RendererID);
	indexBuffer->Bind();
	m_IndexBuffer = indexBuffer;
}
