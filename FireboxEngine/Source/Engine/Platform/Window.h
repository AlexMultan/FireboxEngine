#pragma once

#include "Engine/Core/Core.h"
#include "SDL3/SDL.h"
#include <functional>
#include <vector>

#include "Engine/Events/Event.h"

namespace Firebox {

	using EventCallbackFn = std::function<void(Event&)>;
	using RawEventCallbackFn = std::function<void(const void*)>;

	struct WindowProperties
	{
		const char* title;
		uint32_t width, height;
	};

	class FIREBOX_API Window
	{
		
	private:
		SDL_Window* m_Window;
		SDL_GLContext m_GLContext;
		bool m_Running = true;
		float m_MainScale;

		WindowProperties m_WindowProps;

		uint64_t m_PerformanceCounterStart;
		uint64_t m_PerformanceCounterEnd;
		double m_MaxFPS = 144;

		EventCallbackFn m_EventCallback;
		RawEventCallbackFn m_RawEventCallback;

	public:
		Window(const WindowProperties& windowProps);
		virtual ~Window();

		void Create();
		void PollEvents();
		void SwapBuffers();
		void SetMaxFPS(const double& fps);
		void SetVSyncEnabled(bool enable);
		void PerformanceCounterStart();
		void PerformanceCounterEnd();

		void SetEventCallback(const EventCallbackFn& callback) { m_EventCallback = callback; }
		void SetRawEventCallback(const RawEventCallbackFn& callback) { m_RawEventCallback = callback; }

		inline bool IsRunning()
		{
			return m_Running;
		}

		inline const uint32_t GetWindowWidth() const
		{
			return m_WindowProps.width;
		}

		inline const uint32_t GetWindowHeight() const
		{
			return m_WindowProps.height;
		}

		inline SDL_Window* GetWindow()
		{
			return m_Window;
		}

		inline SDL_GLContext& GetGLContext()
		{
			return m_GLContext;
		}

		inline const float& GetMainScale() const
		{
			return m_MainScale;
		}

		inline void SetIsRunning(bool isRunning)
		{
			m_Running = isRunning;
		}
	};
}