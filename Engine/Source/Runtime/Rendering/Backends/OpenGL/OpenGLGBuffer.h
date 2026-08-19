#pragma once

#include "Rendering/Buffers/GBuffer.h"

namespace Firebox::OpenGL {

	class FIREBOX_API OpenGLGBuffer : public GBuffer
	{
	public:
		OpenGLGBuffer();
		~OpenGLGBuffer();

		virtual void BindGBuffer() override;
		virtual void BindGBufferPositionNormal() override;
		virtual void BindGBufferAO() override;
		virtual void BindGBufferAlbedo() override;
		virtual void UnbindGBuffer() override;
		virtual void BlitGBuffer() override;
		virtual void ReadGBuffer() override;
		virtual void DrawGBuffer(uint targetFBO) override;
		virtual void ResizeGBuffer(uint width, uint height) override;
		virtual void ClearGBuffer() override;
		virtual uint GetColorAttachment() const override;
		virtual GBufferInfo& GetGBufferInfo() override;

	private:
		void Invalidate();

		GBufferInfo m_GBufferInfo{};
	};
}