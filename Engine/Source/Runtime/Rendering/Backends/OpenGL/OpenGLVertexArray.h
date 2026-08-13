#pragma once

#include "Rendering/Buffers/VertexArray.h"

namespace Firebox::OpenGL {

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }
		virtual uint GetID() override { return m_RendererID; }

	private:
		uint32_t m_RendererID = 0;
		Ref<IndexBuffer> m_IndexBuffer;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
	};
}