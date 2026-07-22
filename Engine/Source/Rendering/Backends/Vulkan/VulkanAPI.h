#pragma once

#include "Rendering/RHI/RendererAPI.h"

#include <glad/glad.h>

namespace Firebox::Vulkan {

	class FIREBOX_API VulkanAPI : public RendererAPI
	{
	public:
		VulkanAPI();
		~VulkanAPI();

		virtual void Init() override;
		virtual void ClearColor(const Vector4& color) override;
		virtual void Clear() override;
		virtual void SetViewport(uint x, uint y, uint width, uint height) override;
		virtual void DrawIndexed(const Ref<VertexArray>& vao, uint indexCount = 0) override;
		virtual void SetDepthFunc(APIEnum func) override;
		virtual void ClearDepth(float value) override;
		virtual void Clear(APIEnum func) override;
		virtual void BindTexture(uint slot, uint textureID) override;
		virtual void BindTextureArray(uint slot, uint textureID) override;
		virtual void BindFramebuffer(APIEnum target, uint framebuffer) override;
		virtual void UnbindFramebuffer(APIEnum target) override;
		virtual void BufferSubData(APIEnum target, uint offset, size_t size, const void* data) override;
		virtual void CullFace(APIEnum target) override;

	private:
		static GLenum ToGLEnum(APIEnum value);
	};
}