#include "UniformBuffer.h"
#include "Platform/OpenGL/OpenGLUniformBuffer.h"
#include "Rendering/RendererAPI.h"

Ref<Firebox::UniformBuffer> Firebox::UniformBuffer::Create()
{
	switch (RendererAPI::GetAPI())
	{
	case RendererAPI::API::None:    FB_CORE_ASSERT_LOG("RendererAPI::None is not supported"); return nullptr;
	case RendererAPI::API::OpenGL:  return CreateRef<Firebox::OpenGL::OpenGLUniformBuffer>();
	default:
		FB_CORE_ASSERT_LOG("Unknown RendererAPI!");
		return nullptr;
	}
}