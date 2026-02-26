#include "MenuBar.h"
#include "imgui.h"
#include "Editor/Build/GameRunner.h"

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

            }
            if (ImGui::MenuItem("Save", "Ctrl+S"))
            {

            }
            if (ImGui::MenuItem("Save As", "Ctrl+Shift+S"))
            {

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
