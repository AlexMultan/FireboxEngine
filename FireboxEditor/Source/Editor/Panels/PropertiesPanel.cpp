#include "PropertiesPanel.h"
#include "Engine/Utils/DebugTools.h"
#include "../UI/FloatParameters.h"

#include <imgui.h>

FireboxEditor::PropertiesPanel::PropertiesPanel()
{

}

FireboxEditor::PropertiesPanel::PropertiesPanel(const char* name) : m_Name(name)
{
	
}

FireboxEditor::PropertiesPanel::~PropertiesPanel()
{

}

void FireboxEditor::PropertiesPanel::RenderPanel()
{
	ImGui::Begin(m_Name.c_str());
	FloatParameters float3;

	float3.Float3(&m_PositionParameter, "Location");
	float3.Float3(&m_RotationParameter, "Rotation");
	float3.Float3(&m_ScaleParameter, "Scale");

	ImGui::End();
}

void FireboxEditor::PropertiesPanel::SetDragStrangth(const float& strength)
{
	m_DragStrength = strength;
}


