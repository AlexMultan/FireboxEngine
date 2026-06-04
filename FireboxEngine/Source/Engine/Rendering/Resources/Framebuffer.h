#pragma once

#include "Engine/Core/Core.h"

namespace Firebox {

	struct FramebufferSpecification
	{
		uint Width, Height;
	};

	class FIREBOX_API Framebuffer
	{
	public:
		virtual void BindFramebuffer() = 0;
		virtual void UnbindFramebuffer() = 0;
		virtual void ResizeFramebuffer(uint width, uint height) = 0;
		virtual uint GetColorAttachement() const = 0;

		static Ref<Framebuffer> Create(const FramebufferSpecification& specs);
	};
}