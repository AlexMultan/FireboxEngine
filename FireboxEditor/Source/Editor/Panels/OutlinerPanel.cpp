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

void FireboxEditor::OutlinerPanel::RenderOutlinerPanel()
{
	ImGui::Begin(m_Name.c_str());

	/*ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.05f, 0.5f));
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6.0f);

	if (m_IsButtonClicked)
	{
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.29f, 0.47f, 0.85f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.29f, 0.47f, 0.85f, 0.87f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.49f, 0.68f, 0.91f, 1.0f));
	}
	else
	{
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.09f, 0.09f, 0.09f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.12f, 0.12f, 0.12f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.29f, 0.47f, 0.85f, 1.00f));
	}

	ImGui::PopStyleColor(3);
	ImGui::PopStyleVar(2);*/
	ImGui::End();
}


