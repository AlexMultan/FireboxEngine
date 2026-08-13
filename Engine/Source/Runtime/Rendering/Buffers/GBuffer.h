#pragma once

#include "Core/Core.h"

namespace Firebox {

	struct GBufferInfo
	{
		uint Width;
		uint Height;
		uint Buffer;
		uint Position;
		uint Normal;
		uint AlbedoSpec;
		uint RenderBuffer;
		uint GBufferAttachments[3];
	};

	class FIREBOX_API GBuffer
	{
	public:
		virtual ~GBuffer() = default;

		virtual void BindGBuffer() = 0;
		virtual void BindGBufferPositionNormal() = 0;
		virtual void BindGBufferAlbedo() = 0;
		virtual void UnbindGBuffer() = 0;
		virtual void BlitGBuffer() = 0;
		virtual void ReadGBuffer() = 0;
		virtual void DrawGBuffer(uint targetFBO) = 0;
		virtual void ResizeGBuffer(uint width, uint height) = 0;
		virtual void ClearGBuffer() = 0;
		virtual uint GetColorAttachment() const = 0;
		virtual GBufferInfo& GetGBufferInfo() = 0;

		static Ref<GBuffer> Create();
	};
}