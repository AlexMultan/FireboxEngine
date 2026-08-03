#pragma once

#include <vulkan/vulkan_core.h>

#include <vector>
#include <fstream>

struct SwapchainProps
{
	VkSurfaceCapabilitiesKHR SurfaceCapabilities;
	std::vector<VkSurfaceFormatKHR> Formats;
	std::vector<VkPresentModeKHR> PresentationModes;
};

struct SwapchainImage
{
	VkImage Image;
	VkImageView ImageView;
};

static std::vector<char> ReadFile(const std::string& fileName)
{
	std::ifstream file(fileName, std::ios::binary | std::ios::ate);
}