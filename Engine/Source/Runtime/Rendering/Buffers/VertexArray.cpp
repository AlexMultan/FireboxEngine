#include "VertexArray.h"
#include "Rendering/Backends/OpenGL/OpenGLVertexArray.h"
#include "Rendering/RHI/RendererAPI.h"

Ref<Firebox::VertexArray> Firebox::VertexArray::Create()
{
	switch (RendererAPI::GetAPI())
	{
	case RendererAPI::API::None:    FB_CORE_ASSERT_LOG("RendererAPI::None is not supported"); return nullptr;
	case RendererAPI::API::OpenGL:  return CreateRef<Firebox::OpenGL::OpenGLVertexArray>();
	default:
		FB_CORE_ASSERT_LOG("Unknown RendererAPI!");
		return nullptr;
	}
}
