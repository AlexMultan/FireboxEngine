#pragma once

#include "Rendering/Buffers/VertexArray.h"
#include "Rendering/Buffers/VertexBuffer.h"
#include "Rendering/Buffers/IndexBuffer.h"
#include "Rendering/Buffers/Vertex.h"

namespace Firebox {

	class FIREBOX_API Mesh
	{
	public:
		Mesh(const std::vector<Vertex>& vertices, const std::vector<uint>& indices);
		const Ref<VertexArray>& GetVertexArray() const { return m_VAO; }

	private:
		Ref<VertexArray> m_VAO;
		Ref<VertexBuffer> m_VBO;
		Ref<IndexBuffer> m_IBO;
	};
}

