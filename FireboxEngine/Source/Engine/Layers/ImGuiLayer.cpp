#include "glad/glad.h"
#include "ImGuiLayer.h"
#include "Engine/Core/Application.h"
#include "Engine/Core/Log.h"
#include "glm/glm.hpp"
#include <memory>

Firebox::ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer"), io(nullptr)
{

}

Firebox::ImGuiLayer::~ImGuiLayer()
{

}

void Firebox::ImGuiLayer::OnAttach()
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

    Window& window = Application::Get().GetWindow();
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

void Firebox::ImGuiLayer::OnDetach()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyPlatformWindows();
    ImGui::DestroyContext();
}

void Firebox::ImGuiLayer::OnEvent(SDL_Event& event)
{
    ImGui_ImplSDL3_ProcessEvent(&event);
}

void Firebox::ImGuiLayer::OnImGuiRender()
{
    ImGui::Begin("Properties");

    static glm::vec3 s_position = glm::vec3(50.0f, 20.0f, 0.0f);
    static int counter = 0;

    ImGui::Text("This is some useful text.");               

    ImGui::SliderFloat3("Position", &s_position.x, 0.0f, 1000.0f, "%.2f");

    if (ImGui::Button("Button"))                           
        counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate, io->Framerate);

    ImGui::End();


    ImGui::Begin("Asset Browser");

    ImVec2 folderButtonSize(70.0f, 70.0f);

    if (showFolderButton)
    {
        if (ImGui::Button("Folder", folderButtonSize) && showFolderButton)
        {
            FIREBOX_CORE_INFO("Opened folder!");
            showFolderButton = false;
        }
    }

    if (!showFolderButton)
    {
        if (ImGui::Button("SK_FirstPersonArms", folderButtonSize))
        {
            FIREBOX_CORE_INFO("Opened first person arms model");
        }
    }

    ImGui::End();

}

void Firebox::ImGuiLayer::Begin()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}

void Firebox::ImGuiLayer::End()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        Window& backupMainWindow = Application::Get().GetWindow();
        SDL_Window* backupSDLWindow = backupMainWindow.GetWindow();
        SDL_GLContext backupCurrentContext = backupMainWindow.GetGLContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        SDL_GL_MakeCurrent(backupSDLWindow, backupCurrentContext);
    }

}
