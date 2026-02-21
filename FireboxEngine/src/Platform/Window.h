#pragma once

#include "Core/Core.h"
#include "SDL3/SDL.h"
#include <functional>

namespace Firebox {

	class FIREBOX_API Window
	{
		using EventCallbackFn = std::function<void(SDL_Event&)>;
		
	private:
		EventCallbackFn m_EventCallback;
		SDL_Window* m_Window;
		SDL_GLContext m_GLContext;
		bool m_Running = true;
		const char* m_WindowTitle = "Game";
		uint32_t m_WindowWidth = 1280;
		uint32_t m_WindowHeight = 720;

	public:
		Window(const char* title, uint32_t width, uint32_t height);
		virtual ~Window();

		void Create();
		void PollEvents();
		void SwapBuffers();

		void SetEventCallback(const EventCallbackFn& callback) { m_EventCallback = callback; }

		inline bool IsRunning()
		{
			return m_Running;
		}

		inline const uint32_t GetWindowWidth() const
		{
			return m_WindowWidth;
		}

		inline const uint32_t GetWindowHeight() const
		{
			return m_WindowHeight;
		}

		inline SDL_Window* GetWindow()
		{
			return m_Window;
		}

		inline SDL_GLContext& GetGLContext()
		{
			return m_GLContext;
		}

		inline void SetIsRunning(bool isRunning)
		{
			m_Running = isRunning;
		}
	};
}