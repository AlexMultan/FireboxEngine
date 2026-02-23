#include "glad/glad.h"
#include "Application.h"
#include "Engine/Layers/ImGuiLayer.h"

Firebox::Application* Firebox::Application::s_Instance = nullptr;

Firebox::Application::Application()
{
    s_Instance = this;

    m_Window = std::make_unique<Window>("Roguelike Game", 1280, 720);
    m_Window->Create();
    m_Window->SetEventCallback([this](SDL_Event& event)
        {
            for (Layer* layer : m_LayerStack)
            {
                layer->OnEvent(event);
            }
        });
    m_ImGuiLayer = new ImGuiLayer();
    PushLayer(m_ImGuiLayer);
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

        m_ImGuiLayer->Begin();
        for (Layer* layer : m_LayerStack)
        {
            layer->OnImGuiRender();
        }
        m_ImGuiLayer->End();

        m_Window->SwapBuffers();
        m_Window->PerformanceCounterEnd();
    }
    for (Layer* layer : m_LayerStack)
    {
        layer->OnDetach();
    }
}
