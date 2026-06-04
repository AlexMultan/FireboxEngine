#include "Mesh.h"
#include "Engine/Utils/String.h"

Firebox::Mesh::Mesh(const DynamicArray<Vertex>& vertices, const DynamicArray<uint>& indices)
{
	m_VAO = VertexArray::Create();
	m_VAO->Bind();
	m_VBO = VertexBuffer::Create(vertices.data(), vertices.size() * sizeof(Vertex));
	m_VBO->SetLayout({
		{ ShaderDataType::Float3, "aPos" },
		{ ShaderDataType::Float3, "aNormal" },
		{ ShaderDataType::Float2, "aTexCoords" }
		});

	m_IBO = IndexBuffer::Create(indices.data(), indices.size());
	m_VAO->AddVertexBuffer(m_VBO);
	m_VAO->SetIndexBuffer(m_IBO);
	m_VAO->Unbind();
}
