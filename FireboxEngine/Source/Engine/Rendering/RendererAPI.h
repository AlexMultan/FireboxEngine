#pragma once

#include "Engine/Core/Core.h"
#include "Engine/Rendering/Resources/VertexArray.h"
#include "APIEnum.h"

namespace Firebox {

	class FIREBOX_API RendererAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL = 1
		};

		virtual ~RendererAPI() = default;

		virtual void Init() = 0;
		virtual void SetScreenColor(const Vector4& color) = 0;
		virtual void Clear() = 0;
		virtual void SetViewport(uint x, uint y, uint width, uint height) = 0;
		virtual void DrawIndexed(const Ref<VertexArray>& vao, uint indexCount = 0) = 0;
		virtual void SetDepthFunc(APIEnum func) = 0;
		virtual void ClearDepth(float value) = 0;
		virtual void Clear(APIEnum func) = 0;
		virtual void BindTexture(uint slot, uint textureID) = 0;
		virtual void BindFramebuffer(APIEnum target, uint framebuffer) = 0;
		virtual void UnbindFramebuffer(APIEnum target) = 0;

		static API GetAPI() { return s_API; }
		static Scope<RendererAPI> Create();

	private:
		static API s_API;
	};
}