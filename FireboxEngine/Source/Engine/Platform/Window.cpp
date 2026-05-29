#include "Window.h"
#include "glad/glad.h"
#include "Engine/Core/Log.h"
#include "Engine/Events/SDLEventTranslator.h"

Firebox::Window::Window(const WindowProperties& windowProps) : m_Window(nullptr), m_WindowProps(windowProps)
{
    
}

Firebox::Window::~Window()
{
    SDL_GL_DestroyContext(m_GLContext);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}

void Firebox::Window::Create()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_SetHint(SDL_HINT_VIDEO_ALLOW_SCREENSAVER, "1");
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0");

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    m_MainScale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
    SDL_WindowFlags windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY;

    m_Window = SDL_CreateWindow(
        m_WindowProps.title, (int)(m_WindowProps.width * m_MainScale), (int)(m_WindowProps.height * m_MainScale), windowFlags);

    if (m_Window == NULL)
    {
        FIREBOX_CORE_CRITICAL("Could not create window: %s", SDL_GetError());
    }

    m_GLContext = SDL_GL_CreateContext(m_Window);
    if (!m_GLContext)
    {
        FIREBOX_CORE_CRITICAL("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(m_Window);
        SDL_Quit();
    }
    SDL_GL_MakeCurrent(m_Window, m_GLContext);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        FIREBOX_CORE_CRITICAL("Failed to initialize GLAD");
    }
}

void Firebox::Window::PollEvents()
{
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent))
    {
        if (m_RawEventCallback)
        {
            m_RawEventCallback(&sdlEvent);
        }

        auto event = SDLEventTranslator::Translate(sdlEvent);
        if (!event) { continue; }

        EventDispatcher dispatcher(*event);
        dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& e)
            {
                m_Running = false;
                return true;
            });

        if (m_EventCallback)
        {
            m_EventCallback(*event);
        }
    }
}

void Firebox::Window::SwapBuffers()
{
    SDL_GL_SwapWindow(m_Window);
}

void Firebox::Window::SetMaxFPS(const double& fps)
{
    m_MaxFPS = fps;
}

void Firebox::Window::SetVSyncEnabled(bool enable)
{
    if (enable)
    {
        m_MaxFPS = 60;
    }
}

void Firebox::Window::SetDisplayMode(DisplayMode displayMode)
{
    switch (displayMode)
    {
    case DisplayMode::Windowed:
        m_WindowProps.width = m_SDLDisplayMode.w;
        m_WindowProps.height = m_SDLDisplayMode.h;
        SDL_SetWindowFullscreen(m_Window, false);
		m_DisplayMode = DisplayMode::Windowed;
        break;
    case DisplayMode::Maximized:
#ifdef FIREBOX_PLATFORM_WIN64
        m_SDLDisplayMode.w = GetCurrentMonitorResolution(GetHWND()).workAreaWidth;
        m_SDLDisplayMode.h = GetCurrentMonitorResolution(GetHWND()).workAreaHeight;
#else
        m_SDLDisplayMode.w = 1920;
        m_SDLDisplayMode.h = 1080;
#endif
        m_SDLDisplayMode.format = SDL_PIXELFORMAT_RGBA8888;
        SDL_MaximizeWindow(m_Window);
		m_DisplayMode = DisplayMode::Maximized;
        break;
    default:
        break;
    }
}

void Firebox::Window::PerformanceCounterStart()
{
    m_PerformanceCounterStart = SDL_GetPerformanceCounter();
}

void Firebox::Window::PerformanceCounterEnd()
{
    m_PerformanceCounterEnd = SDL_GetPerformanceCounter();
    double elapsed = (double)(m_PerformanceCounterEnd - m_PerformanceCounterStart) / SDL_GetPerformanceFrequency() * 1000.0;
    if (elapsed < (1000 / m_MaxFPS))
    {
        SDL_Delay((uint)((1000 / m_MaxFPS) - elapsed));
    } 
}

#ifdef FIREBOX_PLATFORM_WIN64

HWND Firebox::Window::GetHWND()
{
	HWND hwnd = nullptr;
	SDL_PropertiesID props = SDL_GetWindowProperties(m_Window);
	if (props != 0)
	{
		hwnd = (HWND)SDL_GetPointerProperty(props, SDL_PROP_WINDOW_WIN32_HWND_POINTER, nullptr);
	}

	if (hwnd != nullptr)
	{
		return hwnd;
	}
	else
	{
		FIREBOX_CORE_ERROR("Failed to get HWND from SDL_Window properties.");
		return nullptr;
	}
}

Firebox::MonitorInfo Firebox::Window::GetCurrentMonitorResolution(HWND hwnd)
{
    HMONITOR hMonitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);

    MONITORINFO monitorInfo;
    monitorInfo.cbSize = sizeof(MONITORINFO);

    if (GetMonitorInfo(hMonitor, &monitorInfo))
    {
        int width = monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left;
        int height = monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top;

        int workAreaWidth = monitorInfo.rcWork.right - monitorInfo.rcWork.left;
        int workAreaHeight = monitorInfo.rcWork.bottom - monitorInfo.rcWork.top;

        return MonitorInfo{ width, height, workAreaWidth, workAreaHeight };
    }
}

#endif
