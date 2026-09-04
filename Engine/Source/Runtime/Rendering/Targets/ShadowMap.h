#pragma once

#include "Core/Core.h"
#include "Core/CoreMinimal.h"

#include <array>

namespace Firebox {

	struct ShadowMapProps
	{
		float Fov, NearPlane, FarPlane, AspectRatio;
		Mat4x4 ViewMatrix;
		Vector3 LightDir;

		ShadowMapProps() = default;
		ShadowMapProps(ShadowMapProps&) = default;
		ShadowMapProps(float fov, float nearPlane, float farPlane, float aspectRatio, const Mat4x4& viewMatrix, const Vector3& lightDir) :
			Fov(fov), NearPlane(nearPlane), FarPlane(farPlane), AspectRatio(aspectRatio), ViewMatrix(viewMatrix), LightDir(lightDir)
		{
		}
	};

	class FIREBOX_API ShadowMap : public RefCounted
	{
	public:
		virtual void BindShadowMap() = 0;
		virtual void UnbindShadowMap() = 0;
		virtual void ResizeFramebuffer(uint resolution) = 0;
		virtual uint GetDepthTexture() const = 0;
		static Ref<ShadowMap> Create(uint resolution);
		
		inline const std::vector<float>& GetCascadeLevels() const { return m_ShadowCascadeLevels; }
		void SetCascadeLevels();
		void SetShadowMapProps(float fov, float nearPlane, float farPlane, float aspectRatio, const Mat4x4& viewMatrix, const Vector3& lightDir);
		std::vector<Vector3> GetFrustumCornersWorldSpace(const Mat4x4& projection, const Mat4x4& view);
		std::vector<Mat4x4> GetLightSpaceMatrices();

	protected:
		ShadowMapProps m_ShadowMapProps;
		uint m_LightDepthMaps = 0;
		uint m_LightFBO = 0;
		uint m_DepthMapResolution = 4096;
		Mat4x4 m_LightSpaceMatrix = Mat4x4(1.0f);
		std::vector<float> m_ShadowCascadeLevels{};
		
	private:
		Mat4x4 GetLightSpaceMatrix(const float nearPlane, const float farPlane);
	};
}