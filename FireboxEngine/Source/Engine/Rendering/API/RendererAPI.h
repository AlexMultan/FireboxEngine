#pragma once

#include "Engine/Core/Core.h"
#include "Engine/Rendering/API/OpenGL/OpenGLShader.h"

namespace Firebox {

	class FIREBOX_API RendererAPI
	{
	private:
		glm::vec3 cubePositions[11] = {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f),
			glm::vec3(0.0f,  -1.0f,  -1.0f)
		};

		Vector3 m_CameraPosition = Vector3(0.0f, 0.0f, 0.0f);
		Vector3 m_CameraFront = Vector3(0.0f, 0.0f, -1.0f);
		Vector3 m_CameraUp = Vector3(0.0f, 1.0f, 0.0f);

		float m_LastMouseX;
		float m_LastMouseY;
		float m_CameraYaw;
		float m_CameraPitch;
		bool m_FirstMouseMovement = true;

		uint m_VAO = 0;
		uint m_VBO = 0;
		uint m_EBO = 0;
		uint m_FBO = 0;
		uint m_RBO = 0;

		uint m_ViewportTextureBuffer;
		Vector2 m_ViewportSize;
		Vector2 m_WindowSize;
		bool m_IsEditorRendering = false;
		bool m_IsViewportFocused = false;

		float m_CameraSpeed = 0.05f;

		Mat4 view = Mat4(1.0f);

		OpenGLShader m_GLShader{};

		uint m_TestTexture;

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

		void ClearEditorViewportRenderingCache();

		inline const Vector3& GetCameraRightVector() const
		{
			return glm::normalize(glm::cross(m_CameraFront, m_CameraUp));
		}

		inline const Vector3& GetCameraFront() const
		{
			return m_CameraFront;
		}

		inline uint GetViewportTextureBuffer() const
		{
			return m_ViewportTextureBuffer;
		}

		inline const Vector2& GetViewportSize()
		{
			return m_ViewportSize;
		}

		inline const Vector2& GetWindowSize()
		{
			return m_WindowSize;
		}

		inline void SetCameraSpeed(float speed)
		{
			m_CameraSpeed = speed;
		}

		inline void SetViewportSize(const Vector2& size)
		{
			m_ViewportSize = size;
		}

		inline void SetWindowSize(const Vector2& size)
		{
			m_WindowSize = size;
		}

		inline void SetEditorViewportRendering(bool editorRendering)
		{
			m_IsEditorRendering = editorRendering;
		}

		inline void SetCubePosition(const Vector3& newPosition)
		{
			cubePositions[0] = newPosition;
		}

		inline void SetCameraPosition(Vector3& newPosition)
		{
			m_CameraPosition = newPosition;
		}

		inline void SetIsViewportFocused(bool isFocused)
		{
			m_IsViewportFocused = isFocused;
		}
	};
}