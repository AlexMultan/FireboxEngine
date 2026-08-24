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
		inline void SetAspectRatio(float aspectRatio) { m_AspectRatio = aspectRatio; }
		virtual const float GetNearPlane() const override { return m_NearPlane; }
		virtual const float GetFarPlane() const override { return m_FarPlane; }
		virtual const float GetFOV() const override { return m_FOV; }
		virtual const float GetAspectRatio() const override { return m_AspectRatio; }

	private:
		float m_FOV;
		float m_AspectRatio;
		float m_NearPlane;
		float m_FarPlane;
	};
}