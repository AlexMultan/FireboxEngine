#pragma once

#include "Rendering/PostProcess/SSAO.h"

namespace Firebox::OpenGL {

	class FIREBOX_API OpenGLSSAO : public SSAO
	{
	public:
		OpenGLSSAO();
		~OpenGLSSAO();

		virtual void BindSSAOBuffer() override;
		virtual void UnbindSSAOBuffer() override;
		virtual void BindSSAOBlurBuffer() override;
		virtual void UnbindSSAOBlurBuffer() override;
		virtual void ResizeSSAOBuffer(uint width, uint height) override;
		virtual void GenerateNoiseTexture() override;
		virtual void BindNoiseTexture() override;
		virtual void BindSSAOTexture() override;
		virtual void BindSSAOBlurTexture() override;

	private:
		void Invalidate();

		uint m_SSAO_FBO;
		uint m_SSAOColorBuffer;
		uint m_SSAOColorBufferBlur;
		uint m_SSAOBlurFBO;
		uint m_NoiseTexture;

		SSAOInfo m_SSAOInfo{};
	};
}