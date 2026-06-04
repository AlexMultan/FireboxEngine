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

	if (m_TransformPropertiesFont)
	{
		PushTreeNodeStyle();

		bool transformTree = ImGui::TreeNodeEx("Transform", ImGuiTreeNodeFlags_Framed);

		PopTreeNodeStyle();

		if (transformTree)
		{
			float3.Float3(&m_PositionParameter, "Location", m_TransformPropertiesFont);
			float3.Float3(&m_RotationParameter, "Rotation", m_TransformPropertiesFont);
			float3.Float3(&m_ScaleParameter, "Scale", m_TransformPropertiesFont);
			ImGui::TreePop();
		}

		/*PushTreeNodeStyle();

		bool detailsTree = ImGui::TreeNodeEx("Details", ImGuiTreeNodeFlags_Framed);

		PopTreeNodeStyle();

		if (detailsTree)
		{
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.86f, 0.86f, 0.86f, 1.0f));
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 2.0f);
			ImGui::Text("Cube Color");
			ImGui::SameLine();
			ImGui::ColorEdit3("##Color", &m_CubeColorParameter.x);

			ImGui::Text("Cube Specular");
			ImGui::SameLine();
			ImGui::DragFloat("##Specular", &m_CubeSpecularParameter, 0.001f, 0.0f, 1.0f);
			ImGui::PopStyleVar();
			ImGui::PopStyleColor();
			ImGui::TreePop();
		}

		PushTreeNodeStyle();
		bool lightSettings = ImGui::TreeNodeEx("Light Settings", ImGuiTreeNodeFlags_Framed);
		PopTreeNodeStyle();

		if (lightSettings)
		{
			float3.Float3(&m_LightDirectionParameter, "Directional Light", m_TransformPropertiesFont);
			float3.Float3(&m_LightPositionParameter, "Point Light", m_TransformPropertiesFont);
			ImGui::TreePop();
		}*/
	}

	ImGui::End();
}

void FireboxEditor::PropertiesPanel::SetDragStrangth(const float& strength)
{
	m_DragStrength = strength;
}

void FireboxEditor::PropertiesPanel::PushTreeNodeStyle()
{
	ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.07f, 0.07f, 0.07f, 0.95f));
	ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.1f, 0.1f, 0.1f, 0.9f));
	ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.12f, 0.12f, 0.12f, 0.9f));
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4.0f, 2.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 7.0f));
}

void FireboxEditor::PropertiesPanel::PopTreeNodeStyle()
{
	ImGui::PopStyleColor(3);
	ImGui::PopStyleVar(3);
}


