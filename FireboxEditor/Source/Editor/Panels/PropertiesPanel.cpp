#include "PropertiesPanel.h"
#include "Engine/Core/Log.h"

FireboxEditor::PropertiesPanel::PropertiesPanel(const char* name) : m_Name(name)
{
	
}

FireboxEditor::PropertiesPanel::~PropertiesPanel()
{

}

void FireboxEditor::PropertiesPanel::RenderPanel()
{
	ImGui::Begin(m_Name.c_str());

	ImGui::InputFloat("Drag Strength", &m_DragStrength, 0.0f, 0.0f, "%.2f");

	ImGui::Separator();
	ImGui::DragFloat3("Position", &m_PositionParameter.x, m_DragStrength, -10000.0f, 10000.0f, "%.2f");
	ImGui::DragFloat3("Rotation", &m_RotationParameter.x, m_DragStrength, -10000.0f, 10000.0f, "%.2f");
	ImGui::DragFloat3("Scale", &m_ScaleParameter.x, m_DragStrength, -10000.0f, 10000.0f, "%.2f");
	ImGui::Separator();

	if (ImGui::Button("Spawn"))
	{
		FIREBOX_EDITOR_INFO("Spawned Entity!");
	}
	ImGui::SameLine();
	ImGui::Text("Spawn Sprite Entity");

	ImGui::End();
}

void FireboxEditor::PropertiesPanel::SetDragStrangth(const float& strength)
{
	m_DragStrength = strength;
}


