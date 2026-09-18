#include "ShadowMap.h"
#include "Rendering/Backends/OpenGL/OpenGLShadowMap.h"
#include "Rendering/RHI/RendererAPI.h"
#include "Utils/String.h"
#include "Utils/Assert.h"
#include "Math/Math.h"

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

	m_ShadowCascadeLevels.emplace_back(m_ShadowMapProps.FarPlane / 100.0f);
	m_ShadowCascadeLevels.emplace_back(m_ShadowMapProps.FarPlane / 50.0f);
	m_ShadowCascadeLevels.emplace_back(m_ShadowMapProps.FarPlane / 25.0f);
	m_ShadowCascadeLevels.emplace_back(m_ShadowMapProps.FarPlane / 10.0f);

	FB_ASSERT(m_ShadowCascadeLevels[0] > m_ShadowMapProps.NearPlane, "Assertion Failed: m_ShadowCascadeLevels[0] is smaller than a near plane!");
}

void Firebox::ShadowMap::SetShadowMapProps(float fov, float nearPlane, float farPlane, float aspectRatio, const Mat4x4& viewMatrix, const Vector3& lightDir)
{
	m_ShadowMapProps.Fov = fov;
	m_ShadowMapProps.NearPlane = nearPlane;
	m_ShadowMapProps.FarPlane = farPlane;
	m_ShadowMapProps.AspectRatio = aspectRatio;
	m_ShadowMapProps.ViewMatrix = viewMatrix;
	m_ShadowMapProps.LightDir = lightDir;
}


std::vector<Mat4x4> Firebox::ShadowMap::GetLightSpaceMatrices()
{
	size_t cascadeCount = m_ShadowCascadeLevels.size();
	std::vector<Mat4x4> ret;
	ret.reserve(cascadeCount);
	for (size_t i = 0; i < cascadeCount; i++)
	{
		float prevSplit = (i == 0) ? m_ShadowMapProps.NearPlane : m_ShadowCascadeLevels[i - 1];
		float nextSplit = m_ShadowCascadeLevels[i];

		ret.emplace_back(GetLightSpaceMatrix(prevSplit, nextSplit));
	}
	return ret;
}

std::vector<Vector3> Firebox::ShadowMap::GetFrustumCornersWorldSpace(const Mat4x4& projection, const Mat4x4& view)
{
	Mat4x4 inverse = glm::inverse(projection * view);

	std::vector<Vector3> corners;
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

Mat4x4 Firebox::ShadowMap::GetLightSpaceMatrix(const float nearPlane, const float farPlane)
{
	const auto proj = glm::perspective(glm::radians(m_ShadowMapProps.Fov), m_ShadowMapProps.AspectRatio, nearPlane, farPlane);
	auto frustumCorners = GetFrustumCornersWorldSpace(proj, m_ShadowMapProps.ViewMatrix);

	Vector3 center(0.0f);
	for (auto& corner : frustumCorners)
		center += corner;
	center /= frustumCorners.size();

	float radius = 0.0f;
	for (const auto& v : frustumCorners)
		radius = std::max(radius, Mathf::Magnitude(v - center));

	radius = std::ceil(radius * 16.0f) / 16.0f;

	Vector3 maxExtents(radius);
	Vector3 minExtents = -maxExtents;

	Vector3 lightDir = Mathf::Normalize(-m_ShadowMapProps.LightDir);
	Mat4x4 lightView = glm::lookAt(center - lightDir * radius, center, Vector3(0.0f, 1.0f, 0.0f));

	constexpr float zOffset = 200.0f;
	float minZ = minExtents.z - zOffset;
	float maxZ = maxExtents.z + zOffset;

#ifdef GLM_FORCE_DEPTH_ZERO_TO_ONE
	Mat4x4 lightProjection = glm::orthoZO(minExtents.x, maxExtents.x, minExtents.y, maxExtents.y, maxZ, minZ);
#else
	Mat4x4 lightProjection = glm::ortho(minExtents.x, maxExtents.x, minExtents.y, maxExtents.y, maxZ, minZ);
#endif

	Mat4x4 shadowMatrix = lightProjection * lightView;
	Vector4 shadowOrigin = shadowMatrix * Vector4(0.0f, 0.0f, 0.0f, 1.0f);
	shadowOrigin *= (static_cast<float>(m_DepthMapResolution) / 2.0f);

	Vector4 roundedOrigin = glm::round(shadowOrigin);
	Vector4 roundOffset = (roundedOrigin - shadowOrigin) * (2.0f / static_cast<float>(m_DepthMapResolution));
	roundOffset.z = 0.0f;
	roundOffset.w = 0.0f;

	lightProjection[3][0] += roundOffset.x;
	lightProjection[3][1] += roundOffset.y;

	return lightProjection * lightView;
}