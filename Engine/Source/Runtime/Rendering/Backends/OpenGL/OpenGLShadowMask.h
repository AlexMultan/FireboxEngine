#pragma once

#include "Rendering/Targets/ShadowMask.h"

namespace Firebox::OpenGL {

	struct ShadowMaskInfo
	{
		uint Width;
		uint Height;
		uint ShadowMaskTexture;
		uint ShadowMaskFBO;
	};
	
	class FIREBOX_API OpenGLShadowMask : public ShadowMask
	{
	public:
		OpenGLShadowMask();
		~OpenGLShadowMask();

		virtual void BindShadowMask() override;
		virtual void BindShadowMaskTexture() override;
		virtual void UnbindShadowMask() override;
		virtual void ResizeShadowMask(uint width, uint height) override;
		virtual void ClearShadowMask() override;

	private:
		void Invalidate();

		ShadowMaskInfo m_ShadowMaskInfo{};
	};
}