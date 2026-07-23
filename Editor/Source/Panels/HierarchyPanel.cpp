#include "HierarchyPanel.h"
#include "UI/EntityHierarchyNode.h"
#include "Scene/Entity.h"
#include "Components/CoreComponents.h"
#include "Components/RenderComponents.h"
#include "Rendering/Geometry/PrimitiveShapes.h"
#include "Rendering/Renderer3D.h"

#include <imgui.h>

FireboxEditor::HierarchyPanel::HierarchyPanel(const char* name, EditorContext& context) : m_Name(name), m_Context(context)
{

}

FireboxEditor::HierarchyPanel::~HierarchyPanel()
{

}

void FireboxEditor::HierarchyPanel::RenderHierarchyrPanel(Ref<Firebox::Scene>& scene)
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 6.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 2.0f));

	ImGui::Begin(m_Name.c_str());

	ImGuiTreeNodeFlags hierarchyNodeFlags = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;

	if (ImGui::TreeNodeEx("Scene", hierarchyNodeFlags))
	{
		for (auto& e : scene->GetAllEntities())
		{
			ImGui::SetCursorPosX(0.0f);
			uint64 id = e.GetComponent<IdComponent>().GetId();
			bool isSelected = m_Context.selectedEntity && (m_Context.selectedEntity.GetComponent<IdComponent>().GetId() == id);
			if (EditorUI::EntityHierarchyNode::DrawNode(e.GetComponent<TagComponent>().Tag.c_str(), id, isSelected))
			{
				m_Context.SetSelected(e);
				FB_EDITOR_TRACE("Selected Entity ID: {0}", id);
			}
		}
		ImGui::TreePop();
	}

	if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !ImGui::IsAnyItemHovered())
	{
		m_Context.ClearSelection();
		FB_EDITOR_TRACE("Deselected Entity. No active node.");
	}

	if (ImGui::IsWindowHovered() && !ImGui::IsAnyItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
		ImGui::OpenPopup("CreatePopup");

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(20.0f, 10.0f));
	ImGuiWindowFlags popupFlags = ImGuiWindowFlags_NoMove;
	if (ImGui::BeginPopup("CreatePopup", popupFlags))
	{
		if (ImGui::BeginMenu("Create"))
		{
			if (ImGui::MenuItem("Empty Entity"))
			{
				Firebox::Entity emptyEntity = scene->CreateEntity("");
				m_Context.SetSelected(emptyEntity);
			}

			if (ImGui::MenuItem("Cube"))
			{
				Firebox::Entity cubeEntity = scene->CreateEntity("Cube");
				m_Context.SetSelected(cubeEntity);
				cubeEntity.AddComponent<MeshComponent>(Firebox::PrimitiveShapes::Cube().vertices, Firebox::PrimitiveShapes::Cube().indices);
				cubeEntity.AddComponent<MaterialComponent>(Firebox::Renderer3D::GetDefaultMaterial());
			}

			if (ImGui::MenuItem("Directional Light"))
			{

			}
			ImGui::EndMenu();
		}
		ImGui::EndPopup();
	}
	ImGui::PopStyleVar(2);
	ImGui::End();
	ImGui::PopStyleVar(3);
}


