#include "EditorViewport.h"
#include "Engine/Core/Application.h"
#include "Engine/Core/Log.h"

#include "glm/glm.hpp"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"

#include <memory>
#include <filesystem>
#include <windows.h>
#include <iostream>

FireboxEditor::EditorViewport::EditorViewport() 
    : Layer("EditorLayer"), io(nullptr), m_AssetBrowser("Asset Browser"), m_PropertiesPanel("PropertiesPanel")
{
    m_MenuBar = FireboxEditor::MenuBar();
    m_DebuggerPanel = FireboxEditor::Debugger();
    STACK(m_AssetBrowser);
    STACK(m_PropertiesPanel);
    STACK(m_MenuBar);
    STACK(m_DebuggerPanel);
}

FireboxEditor::EditorViewport::~EditorViewport()
{
    
}

void FireboxEditor::EditorViewport::OnAttach()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO();
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io->ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports;
    io->ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

    ImGui::StyleColorsDark();

    Firebox::Window& window = Firebox::Application::Get().GetWindow();
    SDL_Window* sdlWindow = window.GetWindow();
    SDL_GLContext glContext = window.GetGLContext();

    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(window.GetMainScale());
    style.FontScaleDpi = window.GetMainScale();
    io->ConfigDpiScaleFonts = true;
    io->ConfigDpiScaleViewports = true;

    if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplSDL3_InitForOpenGL(sdlWindow, glContext);
    ImGui_ImplOpenGL3_Init();
}

void FireboxEditor::EditorViewport::OnDetach()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyPlatformWindows();
    ImGui::DestroyContext();
}

void FireboxEditor::EditorViewport::OnEvent(SDL_Event& event)
{
    ImGui_ImplSDL3_ProcessEvent(&event);
}

void FireboxEditor::EditorViewport::OnEditorUIRender()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    m_DockNodeFlags = ImGuiDockNodeFlags_PassthruCentralNode;
    m_WindowFlags = ImGuiWindowFlags_NoDocking;

    ImGuiViewport* viewport = ImGui::GetMainViewport();

    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    m_WindowFlags |= ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove;
    m_WindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    if (m_DockNodeFlags & ImGuiDockNodeFlags_PassthruCentralNode)
        m_WindowFlags |= ImGuiWindowFlags_NoBackground;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(1.0f, 0.0f));
    ImGui::Begin("Root", nullptr, m_WindowFlags);
    ImGui::PopStyleVar();
    ImGui::PopStyleVar(2);

    if (io->ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspaceID = ImGui::GetID("Root");
        ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), m_DockNodeFlags);
        ImGui::End();
    }

    if (ImGui::Begin("Editor", nullptr, ImGuiWindowFlags_MenuBar))
    {
        m_MenuBar.RenderMenuBar();
        ImGui::End();
    }
    
    m_AssetBrowser.RenderPanel();
    m_PropertiesPanel.RenderPanel();
    m_DebuggerPanel.RenderPanel();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        Firebox::Window& backupMainWindow = Firebox::Application::Get().GetWindow();
        SDL_Window* backupSDLWindow = backupMainWindow.GetWindow();
        SDL_GLContext backupCurrentContext = backupMainWindow.GetGLContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        SDL_GL_MakeCurrent(backupSDLWindow, backupCurrentContext);
    }

}

