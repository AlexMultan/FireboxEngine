#include "Skybox.h"

Firebox::Skybox::Skybox()
{
	m_VAO = VertexArray::Create();
	m_VAO->Bind();
	m_VBO = VertexBuffer::Create(vertices, sizeof(vertices));
	m_VBO->SetLayout({
		{ ShaderDataType::Float3, "aPos" }
		});

	m_IBO = IndexBuffer::Create(indices, 36);
	m_VAO->AddVertexBuffer(m_VBO);
	m_VAO->SetIndexBuffer(m_IBO);
	m_VAO->Unbind();
}
