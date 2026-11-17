#pragma once

#include "Rendering/PostProcess/FXAA.h"

namespace Firebox::OpenGL {

	class FIREBOX_API OpenGLFXAA : public FXAA
	{
	public:
		OpenGLFXAA();
		~OpenGLFXAA();

		virtual void BindFXAABuffer() override;
		virtual void UnbindFXAABuffer() override;
		virtual void ResizeFXAABuffer(uint width, uint height) override;
		virtual uint GetFXAAColorBuffer() override;
		virtual void BindSceneTexture(uint textureID, uint textureUnit) override;
		virtual void BlitToFramebuffer(uint destinationFramebufferID) override;

	private:
		void Invalidate();

		uint m_FXAA_FBO;
		uint m_FXAAColorBuffer;

		FXAAInfo m_FXAAInfo{};
	};
}