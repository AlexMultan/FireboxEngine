#pragma once

#include "Core/Core.h"
#include "Core/CoreMinimal.h"

namespace Firebox {

	struct FramebufferSpecification
	{
		uint Width, Height;
	};

	class FIREBOX_API Framebuffer : public RefCounted
	{
	public:
		virtual void BindFramebuffer() = 0;
		virtual void UnbindFramebuffer() = 0;
		virtual void ResizeFramebuffer(uint width, uint height) = 0;
		virtual void ClearFramebuffer() = 0;
		virtual uint GetColorAttachment() const = 0;
		virtual const FramebufferSpecification& GetSpecs() const = 0;
		virtual const uint GetID() const = 0;

		static Ref<Framebuffer> Create(const FramebufferSpecification& specs);
	};
}