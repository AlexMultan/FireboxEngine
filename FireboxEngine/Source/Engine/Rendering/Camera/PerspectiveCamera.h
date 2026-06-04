#pragma once

#include "Camera.h"

namespace Firebox {
	class FIREBOX_API PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(float fov, float aspectRatio, float nearPlane, float farPlane);
		~PerspectiveCamera();

		virtual Mat4 GetProjectionMatrix() const override;
		inline float GetFOV() const { return m_FOV; }
		inline float GetAspectRatio() const { return m_AspectRatio; }
		inline float GetNearPlane() const { return m_NearPlane; }
		inline float GetFarPlane() const { return m_FarPlane; }

	private:
		float m_FOV;
		float m_AspectRatio;
		float m_NearPlane;
		float m_FarPlane;
	};
}