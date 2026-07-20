#include "VertexBuffer.h"
#include "Rendering/RendererAPI.h"
#include "Platform/OpenGL/OpenGLVertexBuffer.h"

Ref<Firebox::VertexBuffer> Firebox::VertexBuffer::Create(uint size)
{
	switch (RendererAPI::GetAPI())
	{
		case RendererAPI::API::None:    FB_CORE_CRITICAL("API not specified!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexBuffer>(size);
	}
}

Ref<Firebox::VertexBuffer> Firebox::VertexBuffer::Create(const void* vertices, uint size)
{
	switch (RendererAPI::GetAPI())
	{
		case RendererAPI::API::None:    FB_CORE_CRITICAL("API not specified!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexBuffer>(vertices, size);
	}
}
