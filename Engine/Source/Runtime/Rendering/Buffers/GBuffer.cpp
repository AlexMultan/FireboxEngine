#include "GBuffer.h"
#include "Rendering/RHI/RendererAPI.h"
#include "Rendering/Backends/OpenGL/OpenGLGBuffer.h"

Ref<Firebox::GBuffer> Firebox::GBuffer::Create()
{
	switch (RendererAPI::GetAPI())
	{
	case RendererAPI::API::None:    FB_CORE_ASSERT_LOG("RendererAPI::None is not supported"); return nullptr;
	case RendererAPI::API::OpenGL:  return CreateRef<Firebox::OpenGL::OpenGLGBuffer>();
	default:
		FB_CORE_ASSERT_LOG("Unknown RendererAPI!");
		return nullptr;
	}
}
