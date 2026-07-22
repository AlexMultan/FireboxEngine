#include "IndexBuffer.h"
#include "Rendering/RHI/RendererAPI.h"
#include "Rendering/Backends/OpenGL/OpenGLIndexBuffer.h"

Ref<Firebox::IndexBuffer> Firebox::IndexBuffer::Create(const uint* indices, uint count)
{
	switch (RendererAPI::GetAPI())
	{
		case RendererAPI::API::None:    FB_CORE_CRITICAL("API not specified!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLIndexBuffer>(indices, count);
	}
}