#include "EditorSettings.h"
#include "Rendering/Renderer3D.h"
#include "Editor/EditorPaths.h"
#include "Core/EditorUtils.h"
#include "UI/ImGuiHelpers.h"

String FireboxEditor::EditorSettings::s_WindowName = "Editor Settings";

FireboxEditor::EditorSettings::EditorSettings()
{
}

FireboxEditor::EditorSettings::~EditorSettings()
{
}

void FireboxEditor::EditorSettings::ShowWindow(EditorContext& context, bool* isOpen)
{
    if (ImGui::Begin(s_WindowName.c_str(), isOpen))
    {
        static float leftWidth = 70.0f;
        float paneHeight = ImGui::GetContentRegionAvail().y;

        ImGui::BeginChild("LeftPane", ImVec2(leftWidth, paneHeight), true);

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 6.0f));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 2.0f));

        ImGui::Button("Style");

        ImGui::PopStyleVar(3);

        ImGui::EndChild();

        ImGui::SameLine();

        ImGui::Button("##01", ImVec2(6.0f, paneHeight));
        if (ImGui::IsItemActive())
        {
            leftWidth += ImGui::GetIO().MouseDelta.x;
        }

        ImGui::SameLine();

        ImGui::BeginChild("RightPane", ImVec2(0, paneHeight), true);

        if (ImGui::TreeNodeEx("Themes")) 
        {
            ImGui::TreePop();
        }
        ImGui::EndChild();
    }
    ImGui::End();
}
