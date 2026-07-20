#include "Window.h"
#include "Core/Log.h"
#include "Events/SDLEventTranslator.h"
#include "EngineAssets.h"

#include <glad/glad.h>
#include <stb_image.h>

Firebox::Window::Window(const WindowProperties& windowProps) : m_SDLWindow(nullptr), m_WindowProps(windowProps)
{
    
}

Firebox::Window::~Window()
{
    SDL_DestroySurface(m_WindowIcon);
    stbi_image_free(m_WindowIconPixels);
    SDL_GL_DestroyContext(m_GLContext);
    SDL_DestroyWindow(m_SDLWindow);
    SDL_Quit();
}

void Firebox::Window::Create()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

    SDL_SetHint(SDL_HINT_VIDEO_ALLOW_SCREENSAVER, "1");
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0");

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    m_MainScale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
    SDL_WindowFlags windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY;

    int width, height, channels;
    String iconPath = Firebox::EngineAssets::Get("Icons/FireboxEngineLogo32x32.png").string();
    FB_CORE_TRACE(iconPath);
    if (!iconPath.empty())
    {
        m_WindowIconPixels = stbi_load(iconPath.c_str(), &width, &height, &channels, 4);
    }

    if (m_WindowIconPixels)
    {
        m_WindowIcon = SDL_CreateSurfaceFrom(width, height, SDL_PIXELFORMAT_RGBA32, m_WindowIconPixels, width * 4);
    }

    m_SDLWindow = SDL_CreateWindow(
        m_WindowProps.title, (int)(m_WindowProps.width * m_MainScale), (int)(m_WindowProps.height * m_MainScale), windowFlags);

    if (m_SDLWindow == NULL)
    {
        FB_CORE_CRITICAL("Could not create window: %s", SDL_GetError());
    }

    if (!SDL_SetWindowIcon(m_SDLWindow, m_WindowIcon))
    {
        std::cerr << "Failed to set window icon: " << SDL_GetError() << "\n";
    }

    m_GLContext = SDL_GL_CreateContext(m_SDLWindow);
    if (!m_GLContext)
    {
        FB_CORE_CRITICAL("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(m_SDLWindow);
        SDL_Quit();
    }
    SDL_GL_MakeCurrent(m_SDLWindow, m_GLContext);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        FB_CORE_CRITICAL("Failed to initialize GLAD");
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
    SDL_GL_SwapWindow(m_SDLWindow);
}

void Firebox::Window::SetMaxFPS(const double& fps)
{
    m_MaxFPS = fps;
}

void Firebox::Window::SetVSyncEnabled(bool enable)
{
    SDL_GL_SetSwapInterval(enable);
}

void Firebox::Window::SetDisplayMode(DisplayMode displayMode)
{
    if (!m_SDLWindow) return;
    switch (displayMode)
    {
    case DisplayMode::Windowed:
        m_WindowProps.width = m_SDLDisplayMode.w;
        m_WindowProps.height = m_SDLDisplayMode.h;
        SDL_SetWindowFullscreen(m_SDLWindow, false);
		m_DisplayMode = DisplayMode::Windowed;
        break;
    case DisplayMode::Maximized:
    {
#ifdef FIREBOX_PLATFORM_WIN64
        HWND hwnd = GetHWND();
        if (hwnd)
        {
            auto info = GetCurrentMonitorResolution(hwnd);
            m_SDLDisplayMode.w = info.workAreaWidth;
            m_SDLDisplayMode.h = info.workAreaHeight;
        }
#else
        m_SDLDisplayMode.w = 1920;
        m_SDLDisplayMode.h = 1080;
#endif
        m_SDLDisplayMode.format = SDL_PIXELFORMAT_RGBA8888;
        SDL_MaximizeWindow(m_SDLWindow);
        m_DisplayMode = DisplayMode::Maximized;
        break;
    }
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
	SDL_PropertiesID props = SDL_GetWindowProperties(m_SDLWindow);
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
		FB_CORE_ERROR("Failed to get HWND from SDL_Window properties.");
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
