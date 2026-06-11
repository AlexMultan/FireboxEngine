#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Vertex.h"

namespace Firebox {

	class FIREBOX_API Mesh
	{
	public:
		Mesh(const DynamicArray<Vertex>& vertices, const DynamicArray<uint>& indices);
		const Ref<VertexArray>& GetVertexArray() const { return m_VAO; }

	private:
		Ref<VertexArray> m_VAO;
		Ref<VertexBuffer> m_VBO;
		Ref<IndexBuffer> m_IBO;
	};
}