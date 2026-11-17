#include "FXAA.h"
#include "Rendering/RHI/RendererAPI.h"
#include "Rendering/Backends/OpenGL/OpenGLFXAA.h"
#include "Core/Random.h"

Ref<Firebox::FXAA> Firebox::FXAA::Create()
{
	switch (RendererAPI::GetAPI())
	{
	case RendererAPI::API::None:    FB_CORE_ASSERT_LOG("RendererAPI::None is not supported"); return nullptr;
	case RendererAPI::API::OpenGL:  return CreateRef<Firebox::OpenGL::OpenGLFXAA>();
	default:
		FB_CORE_ASSERT_LOG("Unknown RendererAPI!");
		return nullptr;
	}
}
