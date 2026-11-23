#include "ProjectSettings.h"
#include "Rendering/Renderer3D.h"
#include "Editor/EditorPaths.h"
#include "Core/EditorUtils.h"
#include "UI/ImGuiHelpers.h"

String FireboxEditor::ProjectSettings::s_WindowName = "Project Settings";

FireboxEditor::ProjectSettings::ProjectSettings()
{
}

FireboxEditor::ProjectSettings::~ProjectSettings()
{
}

void FireboxEditor::ProjectSettings::ShowWindow(EditorContext& context, bool* isOpen)
{
    if (ImGui::Begin(s_WindowName.c_str(), isOpen))
    {
        ImGui::Text("In Progress");
    }
    ImGui::End();
}
