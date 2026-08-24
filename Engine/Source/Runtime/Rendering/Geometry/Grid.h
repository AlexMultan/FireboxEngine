#pragma once

#include "Rendering/Buffers/VertexArray.h"
#include "Rendering/Buffers/VertexBuffer.h"
#include "Rendering/Buffers/IndexBuffer.h"
#include "Rendering/Buffers/Vertex.h"

namespace Firebox {

	class FIREBOX_API Grid
	{
	public:
		Grid();
		const Ref<VertexArray>& GetVertexArray() const { return m_VAO; }

	private:
		Ref<VertexArray> m_VAO;
		Ref<VertexBuffer> m_VBO;
		Ref<IndexBuffer> m_IBO;

		float vertices[12] = {
			-1.0f,  0.0f,  1.0f,
			 1.0f,  0.0f,  1.0f,
			-1.0f,  0.0f, -1.0f,
			 1.0f,  0.0f, -1.0f
		};

		uint indices[6] = {
			 0, 1, 2,
			 1, 3, 2
		};
	};
}