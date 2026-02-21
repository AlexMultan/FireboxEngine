#include "fireboxpch.h"
#include "ImGuiLayer.h"
#include "Core/Application.h"

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

    ImGui::StyleColorsDark();

    Window& window = Application::Get().GetWindow();
    SDL_Window* sdlWindow = window.GetWindow();
    SDL_GLContext glContext = window.GetGLContext();

    ImGui_ImplSDL3_InitForOpenGL(sdlWindow, glContext);
    ImGui_ImplOpenGL3_Init();
}

void Firebox::ImGuiLayer::OnDetach()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}

void Firebox::ImGuiLayer::OnEvent(SDL_Event& event)
{
    ImGui_ImplSDL3_ProcessEvent(&event);
}

void Firebox::ImGuiLayer::OnImGuiRender()
{
    static float f = 0.0f;
    static int counter = 0;

    ImGui::Text("This is some useful text.");               

    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);           

    if (ImGui::Button("Button"))                           
        counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate, io->Framerate);
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
}
