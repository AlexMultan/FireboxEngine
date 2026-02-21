#include "fireboxpch.h"
#include "Window.h"
#include "glad/glad.h"
#include "Core/Log.h"

Firebox::Window::Window(const char* title, uint32_t width, uint32_t height) 
    : m_Window(nullptr), m_WindowTitle(title), m_WindowWidth(width), m_WindowHeight(height)
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

    m_Window = SDL_CreateWindow(m_WindowTitle, m_WindowWidth, m_WindowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (m_Window == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s", SDL_GetError());
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

    glClearColor(0.42f, 0.56f, 0.91f, 1.0f);
}

void Firebox::Window::PollEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            m_Running = false;
        }

        if (m_EventCallback)
        {
            m_EventCallback(event);
        }
    }
}

void Firebox::Window::SwapBuffers()
{
    SDL_GL_SwapWindow(m_Window);
}

