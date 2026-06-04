#pragma once

#include "Engine/Core/Core.h"
#include "Engine/Components/Components.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Firebox {

	class FIREBOX_API Camera
	{
		enum CameraMovement
		{
			Forward,
			Backward,
			Left,
			Right
		};

	public:
		virtual ~Camera() = default;

		void OnUpdate(float deltaTime);

		void CalculateCameraVectors();
		void ProcessKeyboardInput(float deltaTime);
		void ProcessMouseMovement();

		static Scope<Camera> CreatePerspective(float fov, float aspectRatio, float nearPlane, float farPlane);

		const Vector3& GetPosition() const { return m_Position; }
		const Vector3& GetFront() const { return m_Front; }
		const Mat4& GetViewMatrix() const { return m_ViewMatrix; }
		virtual Mat4 GetProjectionMatrix() const { return Mat4(1.0f); }
		void SetPosition(const Vector3& position) { m_Position = position; RecalculateViewMatrix(); }
		void SetCameraSpeed(float speed) { m_CameraSpeed = speed; }

	protected:
		CameraMovement m_MovementDirection = CameraMovement::Forward;
		float m_Yaw = -90.0f;
		float m_Pitch = 0.0f;
		float m_CameraSpeed = 0.2f;
		float m_MouseSensitivity = 0.1f;

		Vector3 m_Position = Vector3(0.0f, 0.0f, 0.0f);
		Vector3 m_Front = Vector3(0.0f, 0.0f, -1.0f);
		Vector3 m_Up = Vector3(0.0f, 1.0f, 0.0f);
		Vector3 m_Right = Vector3(1.0f, 0.0f, 0.0f);
		Vector3 m_WorldUp = Vector3(0.0f, 1.0f, 0.0f);
		Mat4 m_ViewMatrix = Mat4(1.0f);

		inline void RecalculateViewMatrix()
		{
			m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
		}

	private:
		bool m_FirstMouseMovement = true;
		float m_LastMouseX = 0.0f;
		float m_LastMouseY = 0.0f;
	};
}