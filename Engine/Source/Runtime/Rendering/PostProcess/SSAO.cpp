#include "SSAO.h"
#include "Rendering/RHI/RendererAPI.h"
#include "Rendering/Backends/OpenGL/OpenGLSSAO.h"
#include "Core/Random.h"

Ref<Firebox::SSAO> Firebox::SSAO::Create()
{
	switch (RendererAPI::GetAPI())
	{
	case RendererAPI::API::None:    FB_CORE_ASSERT_LOG("RendererAPI::None is not supported"); return nullptr;
	case RendererAPI::API::OpenGL:  return CreateRef<Firebox::OpenGL::OpenGLSSAO>();
	default:
		FB_CORE_ASSERT_LOG("Unknown RendererAPI!");
		return nullptr;
	}
}

void Firebox::SSAO::GenerateNoiseTexture()
{
	m_SSAONoise.reserve(16);
	for (uint i = 0; i < 16; i++)
	{
		Vector3 noise(Firebox::Random::Range(0.0f, 1.0f) * 2.0f - 1.0f, Firebox::Random::Range(0.0f, 1.0f) * 2.0f - 1.0f, 0.0f);
		m_SSAONoise.emplace_back(noise);
	}
}

void Firebox::SSAO::GenerateSampleKernel()
{
	m_SSAOKernel.reserve(64);
	for (uint i = 0; i < 64; i++)
	{
		Vector3 sample(Firebox::Random::Range(0.0f, 1.0f) * 2.0f - 1.0f, Firebox::Random::Range(0.0f, 1.0f) * 2.0f - 1.0f, Firebox::Random::Range(0.0f, 1.0f));
		sample = glm::normalize(sample);
		sample *= Firebox::Random::Range(0.0f, 1.0f);
		float scale = float(i) / 64.0f;
		scale = Mathf::Lerp(0.1f, 1.0f, scale * scale);
		sample *= scale;
		m_SSAOKernel.emplace_back(sample);
	}
}
