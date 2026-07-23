#include "MenuBar.h"
#include "Build/GameRunner.h"
#include "Input/Input.h"
#include "Editor/EditorPaths.h"
#include "Scene/Entity.h"

#include <imgui.h>
#include <windows.h>
#include <commdlg.h>

FireboxEditor::MenuBar::MenuBar()
{
}

FireboxEditor::MenuBar::~MenuBar()
{
}

void FireboxEditor::MenuBar::RenderMenuBar(Ref<Firebox::Scene>& scene)
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
                OPENFILENAMEW ofn;
                wchar_t szFile[260] = L"";

                ZeroMemory(&ofn, sizeof(ofn));
                ofn.lStructSize = sizeof(ofn);
                ofn.hwndOwner = NULL;
                ofn.lpstrFile = szFile;
                ofn.nMaxFile = sizeof(szFile) / sizeof(wchar_t);
                ofn.lpstrFilter =
                    L"Image Files (*.PNG;*.JPG;*.JPEG;*.BMP)\0*.PNG;*.JPG;*.JPEG;*.BMP\0"
                    L"Text Documents (*.TXT)\0*.TXT\0"
                    L"All Files (*.*)\0*.*\0\0";
                ofn.nFilterIndex = 1;
                ofn.lpstrFileTitle = NULL;
                ofn.nMaxFileTitle = 0;
                ofn.lpstrInitialDir = NULL;
                ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

                if (GetOpenFileNameW(&ofn))
                {
                    std::wstring selectedFile = ofn.lpstrFile;
                }
            }

            if (ImGui::MenuItem("Save", "Ctrl+S"))
            {

            }

            if (ImGui::BeginMenu("Scene"))
            {
                if (ImGui::MenuItem("Save", "Ctrl+Shift+S"))
                {
                    scene->SetSceneName("Untitled");
                    scene->SaveScene(FireboxEditor::Paths::Resource("Levels/Untitled.fbscene").string());
                }

                if (ImGui::MenuItem("Load", "Ctrl+Shift+L"))
                {
                    OPENFILENAMEW ofn;
                    wchar_t szFile[260] = L"";

                    ZeroMemory(&ofn, sizeof(ofn));
                    ofn.lStructSize = sizeof(ofn);
                    ofn.hwndOwner = NULL;
                    ofn.lpstrFile = szFile;
                    ofn.nMaxFile = sizeof(szFile) / sizeof(wchar_t);
                    ofn.lpstrFilter =
                        L"Scene (*.fbscene)\0*.fbscene\0"
                        L"All Files (*.*)\0*.*\0\0";
                    ofn.nFilterIndex = 1;
                    ofn.lpstrFileTitle = NULL;
                    ofn.nMaxFileTitle = 0;
                    ofn.lpstrInitialDir = NULL;
                    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

                    if (GetOpenFileNameW(&ofn))
                    {
                        std::wstring selectedFile = ofn.lpstrFile;
                        size_t len = wcstombs(nullptr, selectedFile.c_str(), 0) + 1;
                        char* buffer = new char[len];
                        wcstombs(buffer, selectedFile.c_str(), len);
                        //scene = scene->LoadScene(buffer);
                        delete[] buffer;
                    }
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

        if (ImGui::BeginMenu("Game"))
        {
            if (ImGui::MenuItem("Run"))
            {
                FireboxEditor::GameRunner gameRunner("Editor/Editor", "SampleGame/SampleGame", FireboxEditor::Extension::EXE);
                gameRunner.RunGame();
            }

            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}
