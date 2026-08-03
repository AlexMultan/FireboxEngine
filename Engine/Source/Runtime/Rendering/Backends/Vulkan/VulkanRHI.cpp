#include "VulkanRHI.h"
#include "Core/Log.h"
#include "Utils/Assert.h"

#include <SDL3/SDL_vulkan.h>

VkInstance Firebox::Vulkan::VulkanRHI::s_Instance = nullptr;
VkSurfaceKHR Firebox::Vulkan::VulkanRHI::s_Surface = nullptr;

Firebox::Vulkan::VulkanRHI::VulkanRHI(SDL_Window* window) : m_Window(window)
{

}

Firebox::Vulkan::VulkanRHI::~VulkanRHI()
{

}

void Firebox::Vulkan::VulkanRHI::Init()
{
	try
	{
		CreateInstance();
		CreateSurface();
	}
	catch(const std::runtime_error& e)
	{
		FB_CORE_CRITICAL(e.what());
		std::exit(EXIT_FAILURE);
	}
}

void Firebox::Vulkan::VulkanRHI::Cleanup()
{
	vkDestroySurfaceKHR(s_Instance, s_Surface, nullptr);
	vkDestroyInstance(s_Instance, nullptr);
}

const VkInstance& Firebox::Vulkan::VulkanRHI::GetInstance()
{
	return s_Instance;
}

const VkSurfaceKHR& Firebox::Vulkan::VulkanRHI::GetSurface()
{
	return s_Surface;
}

void Firebox::Vulkan::VulkanRHI::CreateInstance()
{
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Firebox Editor";
	appInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
	appInfo.pEngineName = "Firebox Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
	appInfo.apiVersion = VK_API_VERSION_1_4;

	VkInstanceCreateInfo instanceCreateInfo{};
	instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceCreateInfo.pApplicationInfo = &appInfo;
	
	std::vector<const char*> instanceExtensions = std::vector<const char*>();
	uint SDLExtensionCount = 0;
	const char* const* SDLExtensions;
	SDLExtensions = SDL_Vulkan_GetInstanceExtensions(&SDLExtensionCount);

	for (int i = 0; i < SDLExtensionCount; i++)
		instanceExtensions.emplace_back(SDLExtensions[i]);

	FB_ASSERT(CheckInstanceExtensionSupport(&instanceExtensions), "VkInstance does not support required extensions!");

	instanceCreateInfo.enabledExtensionCount = static_cast<uint>(instanceExtensions.size());
	instanceCreateInfo.ppEnabledExtensionNames = instanceExtensions.data();
	instanceCreateInfo.enabledLayerCount = 0;
	instanceCreateInfo.ppEnabledLayerNames = nullptr;

	VkResult result = vkCreateInstance(&instanceCreateInfo, nullptr, &s_Instance);
	if (result != VK_SUCCESS)
		FB_CORE_CRITICAL("Failed to create Vulkan Instance!");
}

void Firebox::Vulkan::VulkanRHI::CreateSurface()
{
	bool result = SDL_Vulkan_CreateSurface(m_Window, s_Instance, nullptr, &s_Surface);
}

bool Firebox::Vulkan::VulkanRHI::CheckInstanceExtensionSupport(std::vector<const char*>* checkExtensions)
{
	uint extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> extensions(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

	for (const auto& checkExtension : *checkExtensions)
	{
		bool hasExtension = false;
		for (const auto& extension : extensions)
		{
			if (strcmp(checkExtension, extension.extensionName))
			{
				hasExtension = true;
				break;
			}
		}
		if (!hasExtension)
			return false;
	}
	return true;
}

VkSurfaceFormatKHR Firebox::Vulkan::VulkanRHI::ChooseSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& formats)
{
	if (formats.size() == 1 && formats[0].format == VK_FORMAT_UNDEFINED)
		return { VK_FORMAT_R8G8B8A8_UNORM, VK_COLORSPACE_SRGB_NONLINEAR_KHR };

	for (const auto& surfaceFormat : formats)
	{
		if ((surfaceFormat.format == VK_FORMAT_R8G8B8A8_UNORM || surfaceFormat.format == VK_FORMAT_B8G8R8A8_UNORM) 
			&& surfaceFormat.colorSpace == VK_COLORSPACE_SRGB_NONLINEAR_KHR) return surfaceFormat;
	}
	return formats[0];
}
