#pragma once

#include "Camera.h"

namespace Firebox {
	class FIREBOX_API PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(float fov, float aspectRatio, float nearPlane, float farPlane);
		~PerspectiveCamera();

		virtual Mat4 GetPerspective() const override;
		virtual Mat4 GetPerspectiveInfinite() const override;
		Mat4 ReversePerspective(float fovY, float aspect, float zNear, float zFar) const;
		Mat4 ReversePerspectiveInfinite(float fovY, float aspect, float zNear) const;
		inline float GetFOV() const { return m_FOV; }
		inline float GetAspectRatio() const { return m_AspectRatio; }
		inline void SetAspectRatio(float aspectRatio) { m_AspectRatio = aspectRatio; }
		inline float GetNearPlane() const { return m_NearPlane; }
		inline float GetFarPlane() const { return m_FarPlane; }

	private:
		float m_FOV;
		float m_AspectRatio;
		float m_NearPlane;
		float m_FarPlane;
	};
}