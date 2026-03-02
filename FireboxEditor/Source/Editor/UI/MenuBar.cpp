#include "MenuBar.h"
#include "imgui.h"
#include "Editor/Build/GameRunner.h"
#include "Engine/Input/Input.h"

#include <windows.h>
#include <commdlg.h>

FireboxEditor::MenuBar::MenuBar()
{
}

FireboxEditor::MenuBar::~MenuBar()
{
}

void FireboxEditor::MenuBar::RenderMenuBar()
{
    if (ImGui::BeginMenuBar())
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

            if (ImGui::MenuItem("Save As", "Ctrl+Shift+S"))
            {

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
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Game"))
        {
            if (ImGui::MenuItem("Run"))
            {
                FireboxEditor::GameRunner gameRunner("FireboxEditor/FireboxEditor", "Game/Game", FireboxEditor::Extension::EXE);
                gameRunner.RunGame();
            }

            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
}
