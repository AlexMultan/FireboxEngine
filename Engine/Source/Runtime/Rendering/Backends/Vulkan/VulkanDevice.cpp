#include "VulkanDevice.h"
#include "VulkanRHI.h"
#include "VulkanUtils.h"
#include "Utils/Assert.h"

#include <set>

Firebox::Vulkan::VulkanDevice::VulkanDevice() : m_LogicalDevice(nullptr), m_PhysicalDevice(nullptr), m_GraphicsQueue(nullptr), m_PresentationQueue(nullptr)
{
}

Firebox::Vulkan::VulkanDevice::~VulkanDevice()
{
}

void Firebox::Vulkan::VulkanDevice::GetPhysicalDevice()
{
	uint deviceCount = 0;
	vkEnumeratePhysicalDevices(VulkanRHI::GetInstance(), &deviceCount, nullptr);

	FB_ASSERT(deviceCount == 0, "Could not find GPUs that support Vulkan!");

	std::vector<VkPhysicalDevice> deviceList(deviceCount);
	vkEnumeratePhysicalDevices(VulkanRHI::GetInstance(), &deviceCount, &m_PhysicalDevice);

	for (const auto& device : deviceList)
	{
		if (CheckDeviceSuitable(device))
		{
			m_PhysicalDevice = device;
			break;
		}
	}
}

void Firebox::Vulkan::VulkanDevice::CreateLogicalDevice()
{
	QueueFamiliyIndices indices = GetQueueFamilies(m_PhysicalDevice);

	std::vector<VkDeviceQueueCreateInfo> deviceQueueCreateInfo;
	std::set<int> queueFamilyIndices{ indices.GraphicsFamily, indices.PresentationFamily };

	for (int index : queueFamilyIndices)
	{
		VkDeviceQueueCreateInfo queueCreateInfo{};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = index;
		queueCreateInfo.queueCount = 1;
		float prio = 1.0f;
		queueCreateInfo.pQueuePriorities = &prio;
		deviceQueueCreateInfo.emplace_back(queueCreateInfo);
	}

	VkPhysicalDeviceFeatures deviceFeatures{};
	deviceFeatures.robustBufferAccess = VK_TRUE;
	deviceFeatures.fullDrawIndexUint32 = VK_TRUE;
	deviceFeatures.imageCubeArray = VK_TRUE;
	deviceFeatures.independentBlend = VK_TRUE;
	deviceFeatures.geometryShader = VK_TRUE;
	deviceFeatures.tessellationShader = VK_TRUE;
	deviceFeatures.sampleRateShading = VK_TRUE;
	deviceFeatures.drawIndirectFirstInstance = VK_TRUE;
	deviceFeatures.depthClamp = VK_TRUE;
	deviceFeatures.depthBiasClamp = VK_TRUE;
	deviceFeatures.fillModeNonSolid = VK_TRUE;
	deviceFeatures.depthBounds = VK_TRUE;
	deviceFeatures.wideLines = VK_TRUE;
	deviceFeatures.alphaToOne = VK_TRUE;
	deviceFeatures.multiViewport = VK_TRUE;
	deviceFeatures.samplerAnisotropy = VK_TRUE;
	deviceFeatures.textureCompressionETC2 = VK_TRUE;
	deviceFeatures.shaderTessellationAndGeometryPointSize = VK_TRUE;
	deviceFeatures.shaderImageGatherExtended = VK_TRUE;
	deviceFeatures.shaderStorageImageExtendedFormats = VK_TRUE;
	deviceFeatures.shaderStorageImageMultisample = VK_TRUE;
	deviceFeatures.shaderUniformBufferArrayDynamicIndexing = VK_TRUE;
	deviceFeatures.shaderSampledImageArrayDynamicIndexing = VK_TRUE;
	deviceFeatures.shaderStorageBufferArrayDynamicIndexing = VK_TRUE;
	deviceFeatures.shaderStorageImageArrayDynamicIndexing = VK_TRUE;
	deviceFeatures.shaderClipDistance = VK_TRUE;
	deviceFeatures.shaderCullDistance = VK_TRUE;

	VkDeviceCreateInfo deviceCreateInfo{};
	deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceCreateInfo.queueCreateInfoCount = static_cast<uint>(deviceQueueCreateInfo.size());
	deviceCreateInfo.pQueueCreateInfos = deviceQueueCreateInfo.data();
	deviceCreateInfo.enabledExtensionCount = static_cast<uint>(deviceExtenstions.size());
	deviceCreateInfo.ppEnabledExtensionNames = deviceExtenstions.data();
	deviceCreateInfo.pEnabledFeatures = &deviceFeatures;

	VkResult result = vkCreateDevice(m_PhysicalDevice, &deviceCreateInfo, nullptr, &m_LogicalDevice);
	if (result != VK_SUCCESS)
		FB_CORE_CRITICAL("Failed to create Vulkan Logical Device");

	vkGetDeviceQueue(m_LogicalDevice, indices.GraphicsFamily, 0, &m_GraphicsQueue);
	vkGetDeviceQueue(m_LogicalDevice, indices.PresentationFamily, 0, &m_PresentationQueue);
}

bool Firebox::Vulkan::VulkanDevice::CheckDeviceSuitable(VkPhysicalDevice device)
{
	QueueFamiliyIndices indices = GetQueueFamilies(device);
	bool extensionsSupported = CheckDeviceExtensionSupport(device);

// NOTE: Enable this code block when swapchain is ready
#if 0
	bool swapChainValid = false;

	if (extensionsSupported)
	{
		SwapchainProps swapChainProps = GetSwapchainProps(device);
		swapChainValid = !swapChainProps.PresentationModes.empty() && !swapChainProps.Formats.empty();
	}

	return indices.IsValid() && extensionsSupported && swapChainValid;
#endif
}

bool Firebox::Vulkan::VulkanDevice::CheckDeviceExtensionSupport(VkPhysicalDevice device)
{
	uint extensionCount = 0;
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

	if (extensionCount == 0) return false;

	std::vector<VkExtensionProperties> extensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, extensions.data());

	for (const auto& deviceExtenstion : deviceExtenstions)
	{
		bool hasExtenstion = false;
		for (const auto& extenstion : extensions)
		{
			if (strcmp(deviceExtenstion, extenstion.extensionName) == 0)
			{
				hasExtenstion = true;
				break;
			}
		}

		if (!hasExtenstion) return false;
	}
	return true;
}

Firebox::Vulkan::QueueFamiliyIndices Firebox::Vulkan::VulkanDevice::GetQueueFamilies(VkPhysicalDevice device)
{
	QueueFamiliyIndices indices{};

	uint queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilyPropsList(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilyPropsList.data());

	int i = 0;
	for (const auto& queueFamily : queueFamilyPropsList)
	{
		if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			indices.GraphicsFamily = i;

		VkBool32 presentationSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, VulkanRHI::GetSurface(), &presentationSupport);
		if (queueFamily.queueCount > 0 && presentationSupport)
			indices.PresentationFamily = i;

		if (indices.IsValid()) break;
		i++;
	}
	return indices;
}
