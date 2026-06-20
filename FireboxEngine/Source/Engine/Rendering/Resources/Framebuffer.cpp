#include "Framebuffer.h"
#include "Engine/Platform/OpenGL/OpenGLFramebuffer.h"
#include "Engine/Rendering/RendererAPI.h"

Ref<Firebox::Framebuffer> Firebox::Framebuffer::Create(const FramebufferSpecification& specs)
{
	switch (RendererAPI::GetAPI())
	{
	case RendererAPI::API::None:    FB_CORE_ASSERT_LOG("RendererAPI::None is not supported"); return nullptr;
	case RendererAPI::API::OpenGL:  return CreateRef<Firebox::OpenGL::OpenGLFramebuffer>(specs);
	default:
		FB_CORE_ASSERT_LOG("Unknown RendererAPI!");
		return nullptr;
	}
}