// NOTE: This function will be a part of swapchain creation process. Do not delete!
#if 0 
VkPresentModeKHR Firebox::Vulkan::VulkanRHI::ChoosePresentMode(const std::vector<VkPresentModeKHR>& modes)
{
	for (const auto& mode : modes)
	{
		if (mode == VK_PRESENT_MODE_MAILBOX_KHR)
			return mode;
	}
	return VK_PRESENT_MODE_FIFO_KHR;
}
#endif