#pragma once

#include "Rendering/RHI/RHI.h"

#include <vulkan/vulkan_core.h>
#include <SDL3/SDL.h>

namespace Firebox::Vulkan {

	class FIREBOX_API VulkanRHI : public RHI
	{
	public:
		VulkanRHI(SDL_Window* window);
		~VulkanRHI();

		virtual void Init() override;
		virtual void Cleanup() override;

		static const VkInstance& GetInstance();
		static const VkSurfaceKHR& GetSurface();

	protected:
		virtual void CreateInstance() override;
		virtual void CreateSurface() override;

		virtual [[nondiscard]] bool CheckInstanceExtensionSupport(std::vector<const char*>* checkExtensions) override;

		VkSurfaceFormatKHR ChooseSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& formats);
		VkPresentModeKHR ChoosePresentMode(const std::vector<VkPresentModeKHR>& modes);

	private:
		SDL_Window* m_Window;
		static VkInstance s_Instance;
		static VkSurfaceKHR s_Surface;
	};
}