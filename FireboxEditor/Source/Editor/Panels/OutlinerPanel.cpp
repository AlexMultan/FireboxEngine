#include "OutlinerPanel.h"

#include <imgui.h>

FireboxEditor::OutlinerPanel::OutlinerPanel()
{

}

FireboxEditor::OutlinerPanel::OutlinerPanel(const char* name) : m_Name(name)
{

}

FireboxEditor::OutlinerPanel::~OutlinerPanel()
{

}

void FireboxEditor::OutlinerPanel::RenderPanel()
{
	ImGui::Begin(m_Name.c_str());
	
	ImGui::Text("Is Cube Active");
	ImGui::SameLine();
	ImGui::Checkbox("##active", &m_IsActive);
	
	ImGui::End();
}
