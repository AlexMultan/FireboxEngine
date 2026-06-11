#include "PerspectiveCamera.h"

Firebox::PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float nearPlane, float farPlane) : m_FOV(fov), 
m_AspectRatio(aspectRatio), m_NearPlane(nearPlane), m_FarPlane(farPlane)
{
	CalculateCameraVectors();
}

Firebox::PerspectiveCamera::~PerspectiveCamera()
{

}

Mat4 Firebox::PerspectiveCamera::GetProjectionMatrix() const
{
	return glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearPlane, m_FarPlane);
}
