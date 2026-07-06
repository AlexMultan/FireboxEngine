#include "glad/glad.h"
#include "Application.h"
#include "Engine/Input/Input.h"
#include "Engine/Utils/DebugTools.h"
#include "Engine/Utils/Timer.h"
#include "Engine/Utils/String.h"

Firebox::Application* Firebox::Application::s_Instance = nullptr;

Firebox::Application::Application()
{
    s_Instance = this;
    m_Window = std::make_unique<Window>(WindowProperties("Firebox Editor", 1600, 900));
    m_Window->Create();
    m_Window->SetDisplayMode(DisplayMode::Maximized);
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
    m_Window->SetMaxFPS(144.0f);
    Firebox::Renderer3D::Init();
    for (Layer* layer : m_LayerStack)
    {
        FB_CORE_TRACE("DefaultShader in OnAttach: {0}", (uint64_t)Firebox::Renderer3D::GetDefaultShader().get());
        layer->OnAttach();
    }
	Timer timer;

    m_Window->SetEventCallback([this](Event& e)
        {
            for (auto it = m_LayerStack.begin(); it != m_LayerStack.end(); it++)
            {
                if (e.Handled) break;
                (*it)->OnEvent(e);
            }
        });

    while (m_Window->IsRunning())
    {
        Firebox::Console::SetDrawCalls(0);
        m_Window->PerformanceCounterStart();
        m_Window->PollEvents();

		timer.Tick();

        for (Layer* layer : m_LayerStack)
        {
            layer->OnUpdate(timer.GetDeltaTime());
        }

        for (Layer* layer : m_LayerStack)
        {
            layer->OnRender(timer.GetDeltaTime());
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
    Firebox::Renderer3D::Shutdown();
}
