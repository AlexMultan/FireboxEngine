#pragma once

#include "Rendering/Buffers/VertexArray.h"
#include "Rendering/Buffers/VertexBuffer.h"
#include "Rendering/Buffers/IndexBuffer.h"
#include "Rendering/Buffers/Vertex.h"

namespace Firebox {

	class FIREBOX_API Quad : public RefCounted
	{
	public:
		Quad();
		const Ref<VertexArray>& GetVertexArray() const { return m_VAO; }

	private:
		Ref<VertexArray> m_VAO;
		Ref<VertexBuffer> m_VBO;
		Ref<IndexBuffer> m_IBO;

		float m_Vertices[32] = {
			-1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			 -1.0f,  -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 
			 1.0f,  -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f
		};

		uint m_Indices[6] = {
			 1, 2, 0,
			 1, 3, 2
		};
	};
}
