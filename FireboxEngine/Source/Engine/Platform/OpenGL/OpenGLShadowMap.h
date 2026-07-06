#pragma once

#include "Engine/Rendering/Resources/ShadowMap.h"

namespace Firebox::OpenGL {
	class FIREBOX_API OpenGLShadowMap : public ShadowMap
	{
	public:
		OpenGLShadowMap(uint width, uint height);
		~OpenGLShadowMap();

		virtual void BindFramebuffer() override;
		virtual void UnbindFramebuffer() override;
		virtual void ResizeFramebuffer(uint width, uint height) override;
		virtual uint GetDepthTexture() const override;

	private:
		void Invalidate();

		uint m_DepthMap = 0;
		uint m_DepthMapFBO = 0;
		uint m_Width, m_Height;
	};
}