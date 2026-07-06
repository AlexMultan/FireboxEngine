#pragma once

#include "Framebuffer.h"
#include "Engine/Rendering/Renderer3D.h"

namespace Firebox {

	class FIREBOX_API RenderTarget
	{
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
	};

	class FramebufferTarget : public RenderTarget
	{
	public:
		FramebufferTarget(Ref<Framebuffer> fb) : m_FB(fb) {};
		void Bind() override { m_FB->BindFramebuffer(); }
		void Unbind() override { m_FB->UnbindFramebuffer(); }

	private:
		Ref<Framebuffer> m_FB;
	};
}