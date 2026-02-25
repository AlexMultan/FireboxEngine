#include "EditorViewport.h"
#include "Engine/Core/Application.h"
#include "Engine/Core/Log.h"
#include "glm/glm.hpp"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"

#include <memory>

FireboxEditor::EditorViewport::EditorViewport() 
    : Layer("EditorLayer"), io(nullptr), m_AssetBrowser(nullptr), m_PropertiesPanel(nullptr)
{
    
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

    m_AssetBrowser = new AssetBrowser("Asset Browser");
    m_PropertiesPanel = new PropertiesPanel("Properties");

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
    if (m_AssetBrowser) { delete m_AssetBrowser; }
    if (m_PropertiesPanel) { delete m_PropertiesPanel; }
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

    if (m_AssetBrowser) { m_AssetBrowser->RenderPanel(); }
    if (m_PropertiesPanel) { m_PropertiesPanel->RenderPanel(); }

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
