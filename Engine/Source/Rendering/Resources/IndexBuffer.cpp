#include "IndexBuffer.h"
#include "Rendering/RendererAPI.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"

Ref<Firebox::IndexBuffer> Firebox::IndexBuffer::Create(const uint* indices, uint count)
{
	switch (RendererAPI::GetAPI())
	{
		case RendererAPI::API::None:    FB_CORE_CRITICAL("API not specified!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLIndexBuffer>(indices, count);
	}
}