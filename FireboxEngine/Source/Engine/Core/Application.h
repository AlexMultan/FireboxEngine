#pragma once

#include "Engine/Core/Core.h"
#include "Engine/Layers/LayerStack.h"
#include "Engine/Platform/Window.h"
#include <memory>

namespace Firebox {

	class ImGuiLayer;

	class FIREBOX_API Application
	{
	private:
		static Application* s_Instance;
		LayerStack m_LayerStack;
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;

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
	};

	Application* CreateApp();
}