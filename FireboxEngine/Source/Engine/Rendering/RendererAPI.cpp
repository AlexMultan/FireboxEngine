#include "RendererAPI.h"
#include "Engine/Platform/OpenGL/OpenGLAPI.h"
#include "Engine/Utils/Assert.h"

Firebox::RendererAPI::API Firebox::RendererAPI::s_API = RendererAPI::API::OpenGL;

Scope<Firebox::RendererAPI> Firebox::RendererAPI::Create()
{
	switch (s_API)
	{
		case API::None:    FB_CORE_ASSERT_LOG("RendererAPI::None is not supported"); return nullptr;
		case API::OpenGL:  return CreateScope<Firebox::OpenGL::OpenGLAPI>();
		default:
			FB_CORE_ASSERT_LOG("Unknown RendererAPI!");
			return nullptr;
	}
}
