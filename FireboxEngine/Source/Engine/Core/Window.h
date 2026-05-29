#pragma once

#include "Engine/Core/Core.h"
#include "Engine/Events/Event.h"

#include <SDL3/SDL.h>
#include <functional>
#include <windows.h>

namespace Firebox {

	using EventCallbackFn = std::function<void(Event&)>;
	using RawEventCallbackFn = std::function<void(const void*)>;

	enum DisplayMode
	{
		Windowed = 0,
		Maximized
	};

	struct WindowProperties
	{
		const char* title;
		uint width, height;
	};

	struct MonitorInfo
	{
		int width, height, workAreaWidth, workAreaHeight;
	};

	class FIREBOX_API Window
	{
		
	private:
		SDL_Window* m_Window;
		SDL_GLContext m_GLContext;
		SDL_DisplayMode m_SDLDisplayMode;
		DisplayMode m_DisplayMode = DisplayMode::Maximized;
		bool m_Running = true;
		float m_MainScale;

		WindowProperties m_WindowProps;

		uint64 m_PerformanceCounterStart;
		uint64 m_PerformanceCounterEnd;
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
		void SetDisplayMode(DisplayMode mode);
		void PerformanceCounterStart();
		void PerformanceCounterEnd();

		HWND GetHWND();
		MonitorInfo GetCurrentMonitorResolution(HWND hwnd);

		void SetEventCallback(const EventCallbackFn& callback) { m_EventCallback = callback; }
		void SetRawEventCallback(const RawEventCallbackFn& callback) { m_RawEventCallback = callback; }

		inline bool IsRunning()
		{
			return m_Running;
		}

		inline const uint GetWindowWidth() const
		{
			return m_WindowProps.width;
		}

		inline const uint GetWindowHeight() const
		{
			return m_WindowProps.height;
		}

		inline const Vector2& GetWindowSize() const
		{
			return Vector2(m_WindowProps.width, m_WindowProps.height);
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