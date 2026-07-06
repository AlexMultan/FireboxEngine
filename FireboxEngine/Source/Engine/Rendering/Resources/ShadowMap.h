#pragma once

#include "Engine/Core/Core.h"

namespace Firebox {

	class FIREBOX_API ShadowMap
	{
	public:
		virtual void BindFramebuffer() = 0;
		virtual void UnbindFramebuffer() = 0;
		virtual void ResizeFramebuffer(uint width, uint height) = 0;
		virtual uint GetDepthTexture() const = 0;
		static Ref<ShadowMap> Create(uint width, uint height);
	};
}