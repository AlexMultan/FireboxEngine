#pragma once

#include "Rendering/RHI/RHIDevice.h"

#include <vulkan/vulkan_core.h>

namespace Firebox::Vulkan {

	const std::vector<const char*> deviceExtenstions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	struct QueueFamiliyIndices
	{
		int GraphicsFamily = -1;
		int PresentationFamily = -1;

		bool IsValid() const
		{
			return GraphicsFamily >= 0 && PresentationFamily >= 0;
		}
	};

	class FIREBOX_API VulkanDevice : public RHIDevice
	{
	public:
		VulkanDevice();
		~VulkanDevice();

	protected:
		virtual void GetPhysicalDevice() override;
		virtual void CreateLogicalDevice() override;

	private:
		[[nondiscard]] bool CheckDeviceSuitable(VkPhysicalDevice device);
		[[nondiscard]] bool CheckDeviceExtensionSupport(VkPhysicalDevice device);

		QueueFamiliyIndices GetQueueFamilies(VkPhysicalDevice device);

	private:
		VkPhysicalDevice m_PhysicalDevice;
		VkDevice m_LogicalDevice;
		VkQueue m_GraphicsQueue;
		VkQueue m_PresentationQueue;
	};
}