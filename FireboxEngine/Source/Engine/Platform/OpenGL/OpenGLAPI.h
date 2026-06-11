#pragma once

#include "Engine/Rendering/RendererAPI.h"

namespace Firebox::OpenGL {

	class FIREBOX_API OpenGLAPI : public RendererAPI
	{
	public:
		OpenGLAPI();
		~OpenGLAPI();

		virtual void Init() override;
		virtual void SetScreenColor(const Vector4& color) override;
		virtual void Clear() override;
		virtual void SetViewport(uint x, uint y, uint width, uint height) override;
		virtual void DrawIndexed(const Ref<VertexArray>& vao, uint indexCount = 0) override;
	};
}