#include "Camera.h"
#include "PerspectiveCamera.h"
#include "Engine/Input/Input.h"
#include "Engine/Core/Log.h"
#include "Engine/Utils/String.h"

void Firebox::Camera::OnUpdate(float deltaTime)
{
	if(m_EnableInput)
	{
		ProcessKeyboardInput(deltaTime);
		ProcessMouseMovement();
	}
	else
	{
		m_FirstMouseMovement = true;
	}
	m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

void Firebox::Camera::CalculateCameraVectors()
{
	Vector3 direction;
	direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	direction.y = sin(glm::radians(m_Pitch));
	direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_Front = glm::normalize(direction);
	m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
	m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}

void Firebox::Camera::ProcessKeyboardInput(float deltaTime)
{
	if (Firebox::Input::IsKeyDown(FBK_KEY_W))
	{
		m_Position += (m_CameraSpeed * m_Front) * deltaTime;
	}

	if (Firebox::Input::IsKeyDown(FBK_KEY_S))
	{
		m_Position -= (m_CameraSpeed * m_Front) * deltaTime;
	}

	if (Firebox::Input::IsKeyDown(FBK_KEY_A))
	{
		m_Position -= (m_CameraSpeed * m_Right) * deltaTime;
	}

	if (Firebox::Input::IsKeyDown(FBK_KEY_D))
	{
		m_Position += (m_CameraSpeed * m_Right) * deltaTime;
	}
	
}

void Firebox::Camera::ProcessMouseMovement()
{
	Vector2 mousePos = Firebox::Input::GetMousePosition();

	if (m_FirstMouseMovement)
	{
		m_LastMouseX = mousePos.x;
		m_LastMouseY = mousePos.y;
		m_FirstMouseMovement = false;

		m_Pitch = glm::degrees(asin(m_Front.y));
		m_Yaw = glm::degrees(atan2(m_Front.z, m_Front.x));
	}

	float xOffset = mousePos.x - m_LastMouseX;
	float yOffset = m_LastMouseY - mousePos.y;
	m_LastMouseX = mousePos.x;
	m_LastMouseY = mousePos.y;

	const float sensitivity = 0.1f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	m_Yaw += xOffset;
	m_Pitch += yOffset;

	if (m_Pitch > 89.0f)
	{
		m_Pitch = 89.0f;
	}
	if (m_Pitch < -89.0f)
	{
		m_Pitch = -89.0f;
	}

	CalculateCameraVectors();
}

Scope<Firebox::Camera> Firebox::Camera::CreatePerspective(float fov, float aspectRatio, float nearPlane, float farPlane)
{
	return CreateScope<PerspectiveCamera>(fov, aspectRatio, nearPlane, farPlane);
}
