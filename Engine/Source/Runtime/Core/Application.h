#pragma once

#include "Core/Core.h"
#include "Core/CoreMinimal.h"
#include "Layers/LayerStack.h"
#include "Core/Window.h"

#include <memory>

namespace Firebox {

	class FIREBOX_API Application
	{
	private:
		static Application* s_Instance;
		LayerStack m_LayerStack;
		std::unique_ptr<Window> m_Window;
		std::string m_WindowName;

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