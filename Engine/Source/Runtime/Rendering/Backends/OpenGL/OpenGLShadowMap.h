#pragma once

#include "Rendering/Targets/ShadowMap.h"

namespace Firebox::OpenGL {
	class FIREBOX_API OpenGLShadowMap : public ShadowMap
	{
	public:
		OpenGLShadowMap(uint resolution);
		~OpenGLShadowMap();

		virtual void BindShadowMap() override;
		virtual void UnbindShadowMap() override;
		virtual void ResizeFramebuffer(uint resolution) override;
		virtual uint GetDepthTexture() const override;

	private:
		void Invalidate();
	};
}