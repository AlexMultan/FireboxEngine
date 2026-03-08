#pragma once

#include "Engine/Core/Core.h"
#include "Engine/Layers/LayerStack.h"
#include "Engine/Platform/Window.h"
#include "Engine/Rendering/Renderer2D.h"

#include <memory>

namespace Firebox {

	class FIREBOX_API Application
	{
	private:
		static Application* s_Instance;
		LayerStack m_LayerStack;
		std::unique_ptr<Window> m_Window;
		std::string m_WindowName;
		Ref<Renderer2D> m_Renderer2D;

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

		Renderer2D& GetRenderer2D()
		{
			return *m_Renderer2D;
		}

	};

	Application* CreateApp();
}