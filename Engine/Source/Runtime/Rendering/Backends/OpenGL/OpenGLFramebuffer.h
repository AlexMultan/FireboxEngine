#pragma once

#include "Rendering/Targets/Framebuffer.h"

namespace Firebox::OpenGL {
	class FIREBOX_API OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& specs);
		~OpenGLFramebuffer();

		virtual void BindFramebuffer() override;
		virtual void UnbindFramebuffer() override;
		virtual void ResizeFramebuffer(uint width, uint height) override;
		virtual void ClearFramebuffer() override;
		virtual uint GetColorAttachment() const override { return m_ColorAttachment; }
		virtual const FramebufferSpecification& GetSpecs() const override { return m_Specs; }

	private:
		void Invalidate();

		uint m_ColorAttachment = 0;
		uint m_MsColorTex = 0;
		uint m_FBO = 0;
		uint m_MsFBO = 0;
		uint m_RBO = 0;

		FramebufferSpecification m_Specs;
	};
}