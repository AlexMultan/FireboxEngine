#include "ShadowMap.h"
#include "Rendering/Backends/OpenGL/OpenGLShadowMap.h"
#include "Rendering/RHI/RendererAPI.h"
#include "Utils/String.h"
#include "Utils/Assert.h"

#include <algorithm>
#include <cfloat>
#include <limits>


Ref<Firebox::ShadowMap> Firebox::ShadowMap::Create(uint resolution)
{
	switch (RendererAPI::GetAPI())
	{
	case RendererAPI::API::None:    FB_CORE_ASSERT_LOG("RendererAPI::None is not supported"); return nullptr;
	case RendererAPI::API::OpenGL:  return CreateRef<Firebox::OpenGL::OpenGLShadowMap>(resolution);
	default:
		FB_CORE_ASSERT_LOG("Unknown RendererAPI!");
		return nullptr;
	}
}

void Firebox::ShadowMap::SetCascadeLevels()
{
	m_ShadowCascadeLevels.clear();
	m_ShadowCascadeLevels.reserve(4);

	if (m_ShadowMapProps.FarPlane == 0) [[unlikely]]
		m_ShadowMapProps.FarPlane = 1000;

	m_ShadowCascadeLevels.emplace_back(m_ShadowMapProps.FarPlane / 50.0f);
	m_ShadowCascadeLevels.emplace_back(m_ShadowMapProps.FarPlane / 25.0f);
	m_ShadowCascadeLevels.emplace_back(m_ShadowMapProps.FarPlane / 10.0f);
	m_ShadowCascadeLevels.emplace_back(m_ShadowMapProps.FarPlane / 2.0f);

	FB_ASSERT(m_ShadowCascadeLevels[0] > m_ShadowMapProps.NearPlane, "m_ShadowCascadeLevels[0] is smaller than a near plane!");
}

void Firebox::ShadowMap::SetShadowMapProps(float fov, float nearPlane, float farPlane, float aspectRatio, const Mat4& viewMatrix, const Vector3& lightDir)
{
	m_ShadowMapProps.Fov = fov;
	m_ShadowMapProps.NearPlane = nearPlane;
	m_ShadowMapProps.FarPlane = farPlane;
	m_ShadowMapProps.AspectRatio = aspectRatio;
	m_ShadowMapProps.ViewMatrix = viewMatrix;
	m_ShadowMapProps.LightDir = lightDir;
}


DynamicArray<Mat4> Firebox::ShadowMap::GetLightSpaceMatrices()
{
	DynamicArray<Mat4> ret;
	size_t cascadeCount = m_ShadowCascadeLevels.size();
	ret.reserve(cascadeCount);
	for (size_t i = 0; i < cascadeCount; i++)
	{
		float prevSplit = (i == 0) ? m_ShadowMapProps.NearPlane : m_ShadowCascadeLevels[i - 1];
		float nextSplit = m_ShadowCascadeLevels[i];

		ret.emplace_back(GetLightSpaceMatrix(prevSplit, nextSplit));
	}
	return ret;
}

DynamicArray<Vector3> Firebox::ShadowMap::GetFrustumCornersWorldSpace(const Mat4& projection, const Mat4& view)
{
	Mat4 inverse = glm::inverse(projection * view);

	DynamicArray<Vector3> corners;
	corners.reserve(8);
	for (int x = 0; x < 2; x++)
	{
		for (int y = 0; y < 2; y++)
		{
			for (int z = 0; z < 2; z++)
			{
				Vector4 pt = inverse * Vector4(
					2.0f * x - 1.0f,
					2.0f * y - 1.0f,
					2.0f * z - 1.0f,
					1.0f
				);
				corners.emplace_back(Vector3(pt) / pt.w);
			}
		}
	}
	return corners;
}

Mat4 Firebox::ShadowMap::GetLightSpaceMatrix(const float nearPlane, const float farPlane)
{
	const auto proj = glm::perspective(glm::radians(m_ShadowMapProps.Fov), m_ShadowMapProps.AspectRatio, nearPlane, farPlane);
	auto frustumCorners = GetFrustumCornersWorldSpace(proj, m_ShadowMapProps.ViewMatrix);

	Vector3 center(0.0f);
	for (auto& corner : frustumCorners)
		center += Vector3(corner);
	center /= frustumCorners.size();

	Vector3 lightDir = glm::normalize(-m_ShadowMapProps.LightDir);
	Mat4 lightView = glm::lookAt(center + lightDir * 50.0f, center, Vector3(0.0f, 1.0f, 0.0f));

	float minX = std::numeric_limits<float>::max();
	float maxX = std::numeric_limits<float>::lowest();
	float minY = std::numeric_limits<float>::max();
	float maxY = std::numeric_limits<float>::lowest();
	float minZ = std::numeric_limits<float>::max();
	float maxZ = std::numeric_limits<float>::lowest();

	for (const auto& v : frustumCorners)
	{
		const auto lightSpaceCorner = lightView * Vector4(v, 1.0f);
		minX = std::min(minX, lightSpaceCorner.x);
		maxX = std::max(maxX, lightSpaceCorner.x);
		minY = std::min(minY, lightSpaceCorner.y);
		maxY = std::max(maxY, lightSpaceCorner.y);
		minZ = std::min(minZ, lightSpaceCorner.z);
		maxZ = std::max(maxZ, lightSpaceCorner.z);
	}

	// TODO: replace with light space union of scene caster AABBs once frustum culling tracks object bounds

	constexpr float zOffset = 200.0f;
	if (minZ < 0) minZ -= zOffset; else minZ -= zOffset;
	if (maxZ < 0) maxZ += zOffset; else maxZ += zOffset;

#ifdef GLM_FORCE_DEPTH_ZERO_TO_ONE
	Mat4 lightProjection = glm::orthoZO(minX, maxX, minY, maxY, minZ, maxZ);
#else
	Mat4 lightProjection = glm::ortho(minX, maxX, minY, maxY, minZ, maxZ);
#endif
	return lightProjection * lightView;
}