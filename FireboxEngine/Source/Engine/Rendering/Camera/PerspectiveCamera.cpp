#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include "PerspectiveCamera.h"

Firebox::PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float nearPlane, float farPlane) : m_FOV(fov), 
m_AspectRatio(aspectRatio), m_NearPlane(nearPlane), m_FarPlane(farPlane)
{
	CalculateCameraVectors();
}

Firebox::PerspectiveCamera::~PerspectiveCamera()
{

}

Mat4 Firebox::PerspectiveCamera::GetPerspective() const
{
	return ReversePerspective(glm::radians(m_FOV), m_AspectRatio, m_NearPlane, m_FarPlane);
}

Mat4 Firebox::PerspectiveCamera::GetPerspectiveInfinite() const
{
	return ReversePerspectiveInfinite(glm::radians(m_FOV), m_AspectRatio, m_NearPlane);
}

Mat4 Firebox::PerspectiveCamera::ReversePerspective(float fovY, float aspect, float zNear, float zFar) const
{
	float f = 1.0f / tanf(fovY / 2.0f);
	Mat4 proj(0.0f);
	proj[0][0] = f / aspect;
	proj[1][1] = f;
	proj[2][2] = zNear / (zFar - zNear);
	proj[2][3] = -1.0f;
	proj[3][2] = (zNear * zFar) / (zFar - zNear);
	return proj;
}
Mat4 Firebox::PerspectiveCamera::ReversePerspectiveInfinite(float fovY, float aspect, float zNear) const
{
	float f = 1.0f / tanf(fovY / 2.0f);
	Mat4 proj(0.0f);
	proj[0][0] = f / aspect;
	proj[1][1] = f;
	proj[2][2] = 0.0f;
	proj[2][3] = -1.0f;
	proj[3][2] = zNear;
	return proj;
}



