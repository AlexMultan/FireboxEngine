#include "Quad.h"

Firebox::Quad::Quad()
{
	m_VAO = VertexArray::Create();
	m_VAO->Bind();
	m_VBO = VertexBuffer::Create(m_Vertices, sizeof(m_Vertices));
	m_VBO->SetLayout({
		{ ShaderDataType::Float3, "aPos" },
		{ ShaderDataType::Float3, "aNormal" },
		{ ShaderDataType::Float2, "aTexCoords" }
		});

	m_IBO = IndexBuffer::Create(m_Indices, 6);
	m_VAO->AddVertexBuffer(m_VBO);
	m_VAO->SetIndexBuffer(m_IBO);
	m_VAO->Unbind();
}
