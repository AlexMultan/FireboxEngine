#include "RHI.h"
#include "Rendering/Backends/Vulkan/VulkanRHI.h"
#include "Utils/Assert.h"

Firebox::RHI::API Firebox::RHI::s_API = RHI::API::Vulkan;

Scope<Firebox::RHI> Firebox::RHI::Create(SDL_Window* window)
{
	switch (s_API)
	{
	case API::None:    FB_CORE_ASSERT_LOG("RHI::None is not supported"); return nullptr;
	case API::Vulkan:  return CreateScope<Firebox::Vulkan::VulkanRHI>(window);
	default:
		FB_CORE_ASSERT_LOG("Unknown RendererAPI!");
		return nullptr;
	}
}