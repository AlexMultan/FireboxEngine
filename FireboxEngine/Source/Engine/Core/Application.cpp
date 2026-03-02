#include "glad/glad.h"
#include "Application.h"
#include "Engine/Input/Input.h"

Firebox::Application* Firebox::Application::s_Instance = nullptr;

Firebox::Application::Application()
{
    s_Instance = this;
    m_Window = std::make_unique<Window>(WindowProperties("Firebox Editor", 1600, 900));
    m_Window->Create();
}

Firebox::Application::~Application()
{
    
}

void Firebox::Application::PushLayer(Layer* layer)
{
    m_LayerStack.PushLayer(layer);
}

void Firebox::Application::PushOverlay(Layer* layer)
{
    m_LayerStack.PushOverlay(layer);
}

void Firebox::Application::Run()
{
    for (Layer* layer : m_LayerStack)
    {
        layer->OnAttach();
    }

    m_Window->SetEventCallback([this](Event& e)
        {
            for (auto it = m_LayerStack.begin(); it != m_LayerStack.end(); ++it)
            {
                if (e.Handled) break;
                (*it)->OnEvent(e);
            }
        });

    while (m_Window->IsRunning())
    {
        m_Window->PerformanceCounterStart();
        m_Window->PollEvents();

        for (Layer* layer : m_LayerStack)
        {
            layer->OnUpdate();
        }

        glClear(GL_COLOR_BUFFER_BIT);

        for (Layer* layer : m_LayerStack)
        {
            layer->OnRender();
        }

        for (Layer* layer : m_LayerStack)
        {
            layer->OnEditorUIRender();
        }

        Firebox::Input::OnInputUpdate();

        m_Window->SwapBuffers();
        m_Window->PerformanceCounterEnd();
    }
    for (Layer* layer : m_LayerStack)
    {
        layer->OnDetach();
    }
}
