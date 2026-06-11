#pragma once

#include "Engine/Rendering/Resources/VertexBuffer.h"


namespace Firebox {

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(uint size);
		OpenGLVertexBuffer(const void* data, uint size);
		~OpenGLVertexBuffer();

		virtual void BindBuffer() const override;
		virtual void UnbindBuffer() const override;
		virtual void SetBufferData(const void* data, uint size) override;
		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
		virtual uint GetBufferID() const { return m_RendererID; }

	private:
		uint m_RendererID = 0;
		BufferLayout m_Layout;
	};
}