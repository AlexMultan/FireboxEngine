#pragma once

#include "Engine/Core/Core.h"
#include "Engine/Rendering/API/OpenGL/OpenGLShader.h"

namespace Firebox {

	class FIREBOX_API RendererAPI
	{
	private:
		float m_VertexData[24] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
			 -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f
		};

		uint m_Indices[6] = {
			0, 1, 2,
			2, 3, 0
		};

		uint m_VAO;
		uint m_VBO;
		uint m_EBO;
		uint m_FBO;

		uint m_ViewportTextureBuffer;
		Vector2 m_ViewportSize;
		bool m_UseFramebuffer = false;

		OpenGLShader m_GLShader{};

	public:
		RendererAPI();
		~RendererAPI();

		void Init();
		void BindBuffers();
		void UnbindBuffers();

		void SetScreenColor(const Vector4& color);
		void Clear();
		void RenderQuad();
		void ResizeFramebuffer(uint32_t width, uint32_t height);

		inline uint GetViewportTextureBuffer()
		{
			return m_ViewportTextureBuffer;
		}

		inline const Vector2& GetViewportSize()
		{
			return m_ViewportSize;
		}

		inline void SetViewportSize(const Vector2& size)
		{
			m_ViewportSize = size;
		}

		inline void SetUseFramebuffer(bool useFramebuffer)
		{
			m_UseFramebuffer = useFramebuffer;
		}
	};
}