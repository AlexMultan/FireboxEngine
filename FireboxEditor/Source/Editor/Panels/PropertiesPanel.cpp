#include "PropertiesPanel.h"
#include "Editor/UI/FloatParameters.h"
#include "Engine/Utils/DebugTools.h"
#include "Engine/Components/Components.h"
#include "Engine/Scene/Entity.h"

#include <imgui.h>

FireboxEditor::PropertiesPanel::PropertiesPanel(const char* name, EditorContext& context) : m_Name(name), m_Context(context)
{
	
}

FireboxEditor::PropertiesPanel::~PropertiesPanel()
{

}

void FireboxEditor::PropertiesPanel::RenderPanel()
{
	Firebox::Entity entity = m_Context.selectedEntity;

	ImGui::Begin(m_Name.c_str());

	if (entity)
	{
		if (entity.HasComponent<TransformComponent>() && m_TransformPropertiesFont)
		{
			FloatParameters float3;
			PushTreeNodeStyle();

			ImGuiTreeNodeFlags transformTreeFlags = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_DefaultOpen;
			bool transformTree = ImGui::TreeNodeEx("Transform", transformTreeFlags);

			PopTreeNodeStyle();

			if (transformTree)
			{
				float3.Float3(&entity.GetComponent<TransformComponent>().Position, "Location", m_TransformPropertiesFont);
				float3.Float3(&entity.GetComponent<TransformComponent>().Rotation, "Rotation", m_TransformPropertiesFont);
				float3.Float3(&entity.GetComponent<TransformComponent>().Scale, "Scale", m_TransformPropertiesFont);
				ImGui::TreePop();
			}
		}
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
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4.0f, 2.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 7.0f));
}

void FireboxEditor::PropertiesPanel::PopTreeNodeStyle()
{
	ImGui::PopStyleColor(3);
	ImGui::PopStyleVar(2);
}


