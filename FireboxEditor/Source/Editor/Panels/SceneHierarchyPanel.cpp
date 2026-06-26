#include "SceneHierarchyPanel.h"
#include "../UI/EntityOutlinerNode.h"
#include "Engine/Scene/Entity.h"
#include "Engine/Components/Components.h"

#include <imgui.h>

FireboxEditor::SceneHierarchyPanel::SceneHierarchyPanel(const char* name, EditorContext& context) : m_Name(name), m_Context(context)
{

}

FireboxEditor::SceneHierarchyPanel::~SceneHierarchyPanel()
{

}

void FireboxEditor::SceneHierarchyPanel::RenderSceneHierarchyrPanel(Ref<Firebox::Scene>& scene)
{
	EntityOutlinerNode entityNode{};

	ImGui::Begin(m_Name.c_str());

	for (auto& e : scene->GetAllEntities())
	{
		uint64 id = e.GetComponent<IdComponent>().GetId();
		bool isSelected = m_Context.selectedEntity && (m_Context.selectedEntity.GetComponent<IdComponent>().GetId() == id);
		if (entityNode.DrawNode(e.GetComponent<TagComponent>().Tag.c_str(), id, isSelected))
		{
			m_Context.SetSelected(e);
			FB_EDITOR_INFO("Selected Entity ID: {0}", id);
		}
	}

	if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !ImGui::IsAnyItemHovered())
	{
		m_Context.ClearSelection();
		FB_EDITOR_INFO("Deselected Entity. No active node.");
	}
	
	ImGui::End();
}


