#pragma once

#include "Core/Core.h"
#include "Layers/LayerStack.h"
#include "Core/Window.h"
#include "Rendering/RHI/RHI.h"

namespace Firebox {

	class FIREBOX_API Application
	{
	public:
		Application();
		~Application();

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		static Application& Get()
		{
			return *s_Instance;
		}

		Window& GetWindow()
		{
			return *m_Window;
		}

	private:
		static Application* s_Instance;
		LayerStack m_LayerStack;
		std::unique_ptr<Window> m_Window;
		std::string m_WindowName;
		Scope<RHI> m_RHI;
	};

	Application* CreateApp();

}