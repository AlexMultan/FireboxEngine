#include "ShadowMap.h"
#include "Engine/Platform/OpenGL/OpenGLShadowMap.h"
#include "Engine/Rendering/RendererAPI.h"

Ref<Firebox::ShadowMap> Firebox::ShadowMap::Create(uint width, uint height)
{
	switch (RendererAPI::GetAPI())
	{
	case RendererAPI::API::None:    FB_CORE_ASSERT_LOG("RendererAPI::None is not supported"); return nullptr;
	case RendererAPI::API::OpenGL:  return CreateRef<Firebox::OpenGL::OpenGLShadowMap>(width, height);
	default:
		FB_CORE_ASSERT_LOG("Unknown RendererAPI!");
		return nullptr;
	}
}