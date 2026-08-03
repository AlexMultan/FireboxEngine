#pragma once

#include "Core/Core.h"
#include "APIEnum.h"
#include "Core/Window.h"

namespace Firebox {

	class FIREBOX_API RHI
	{
	public:
		enum class API
		{
			None = 0,
			Vulkan = 1
		};

		virtual ~RHI() = default;

		virtual void Init() = 0;
		virtual void Cleanup() = 0;

		static API GetAPI() { return s_API; }
		static [[nodiscard]] Scope<RHI> Create(SDL_Window* window);

	protected:
		virtual void CreateInstance() = 0;
		virtual void CreateSurface() = 0;

		virtual [[nondiscard]] bool CheckInstanceExtensionSupport(std::vector<const char*>* checkExtensions = nullptr) = 0;

	private:
		static API s_API;
		SDL_Window* m_Window;
	};
}