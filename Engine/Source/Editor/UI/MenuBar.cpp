#include "MenuBar.h"
#include "Input/Input.h"
#include "Editor/EditorPaths.h"
#include "Scene/Entity.h"

#include <imgui.h>

FireboxEditor::MenuBar::MenuBar(FireboxEditor::EditorContext& context) : m_Context(context), m_Scene(nullptr)
{
    m_Context.AddSceneChangeListener([this](const Ref<Firebox::Scene>& newScene)
        {
            m_Scene = newScene;
        });
}

FireboxEditor::MenuBar::~MenuBar()
{
}

void FireboxEditor::MenuBar::RenderMenuBar()
{
    static bool s_ShowProjectSettings = false;

    if (s_ShowProjectSettings)
    {
        ImGui::Begin("Project Settings");
        if (ImGui::Button("Close"))
        {
            s_ShowProjectSettings = false;
        }
        ImGui::Text("In Progress");
        ImGui::End();
    }

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New"))
            {

            }
            if (ImGui::MenuItem("Open", "Ctrl+O"))
            {
                
            }

            if (ImGui::MenuItem("Save", "Ctrl+S"))
            {

            }

            if (ImGui::BeginMenu("Scene"))
            {
                if (ImGui::MenuItem("Save", "Ctrl+Shift+S"))
                {
                    m_Context.GetCurrentScene()->SetSceneName("Untitled");
                    m_Context.GetCurrentScene()->SaveScene(FireboxEditor::EditorContent::Get("Levels/Untitled.fbscene").string());
                }

                if (ImGui::MenuItem("Load", "Ctrl+Shift+L"))
                {
                    SDL_ShowOpenFileDialog(Callback, NULL, nullptr, nullptr, 0,
                        FireboxEditor::EditorContent::GetRootPath().string().c_str(), true);
                    
                }
                ImGui::EndMenu();
            }

            if (ImGui::MenuItem("Exit"))
            {
                std::exit(EXIT_SUCCESS);
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "Ctrl+Z"))
            {

            }
            if (ImGui::MenuItem("Redo", "Ctrl+Y", false, false))
            {

            }
            ImGui::Separator();
            if (ImGui::MenuItem("Copy", "Ctrl+C"))
            {

            }
            if (ImGui::MenuItem("Paste", "Ctrl+V"))
            {

            }
            if (ImGui::MenuItem("Cut", "Ctrl+X"))
            {

            }
            ImGui::Separator();
            if (ImGui::MenuItem("Project Settings"))
            {
                s_ShowProjectSettings = true;
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}

void SDLCALL FireboxEditor::MenuBar::Callback(void* userdata, const char* const* filelist, int filter)
{
    if (!filelist)
    {
        SDL_Log("An error occured: %s", SDL_GetError());
        return;
    }
    else if (!*filelist)
    {
        SDL_Log("The user did not select any file.");
        SDL_Log("Most likely, the dialog was canceled.");
        return;
    }

    while (*filelist)
    {
        SDL_Log("Full path to selected file: '%s'", *filelist);
        filelist++;
    }
}


