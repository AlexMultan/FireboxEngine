#pragma once

#include "Engine/Rendering/Resources/IndexBuffer.h"

namespace Firebox {

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(const uint* indices, uint count);
		~OpenGLIndexBuffer();

		virtual void Bind() override;
		virtual void Unbind() override;
		virtual uint GetCount() const override { return m_Count; }
		virtual uint GetBufferID() const { return m_RendererID; }

	private:
		uint m_RendererID = 0;
		uint m_Count = 0;
	};
}