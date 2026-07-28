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
	m_Context.AddEntitySelectionListener([this](Firebox::Entity newEntity)
		{
			m_SelectedEntity = newEntity;
		});
}

FireboxEditor::HierarchyPanel::~HierarchyPanel()
{

}

void FireboxEditor::HierarchyPanel::RenderHierarchyrPanel(const Ref<Firebox::Scene>& scene)
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 6.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 2.0f));

	ImGui::Begin(m_Name.c_str());

	ImGuiTreeNodeFlags hierarchyNodeFlags = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;

	if (ImGui::TreeNodeEx("Scene", hierarchyNodeFlags))
	{
		auto& registry = scene->GetRegistry();
		for (auto e : registry.view<IdComponent>())
		{
			ImGui::SetCursorPosX(0.0f);
			uint64 id = registry.get<IdComponent>(e).GetId();
			bool isSelected = m_SelectedEntity && (m_SelectedEntity.GetComponent<IdComponent>().GetId() == id);
			if (EditorUI::EntityHierarchyNode::DrawNode(registry.get<TagComponent>(e).Tag.c_str(), id, isSelected))
			{
				m_Context.SetSelectedEntity(Firebox::Entity(e, scene.get()));
				FB_EDITOR_TRACE("Selected Entity ID: {0}", id);
			}
		}
		ImGui::TreePop();
	}

	if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !ImGui::IsAnyItemHovered())
	{
		m_Context.DeselectEntity();
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
				m_Context.SetSelectedEntity(emptyEntity);
			}

			if (ImGui::MenuItem("Cube"))
			{
				Firebox::Entity cubeEntity = scene->CreateEntity("Cube");
				m_Context.SetSelectedEntity(cubeEntity);
				cubeEntity.AddComponent<MeshComponent>(Firebox::PrimitiveShapes::Cube().vertices, Firebox::PrimitiveShapes::Cube().indices);
				cubeEntity.AddComponent<MaterialComponent>(Firebox::Renderer3D::GetDefaultMaterial());
			}

			if (ImGui::MenuItem("Directional Light"))
			{
				Firebox::Entity directionalLightEntity = scene->CreateEntity("Directional Light");
				m_Context.SetSelectedEntity(directionalLightEntity);
				directionalLightEntity.AddComponent<DirectionalLightComponent>();
				directionalLightEntity.GetComponent<DirectionalLightComponent>().Direction = { -0.2f, -1.0f, -0.3f };
				directionalLightEntity.GetComponent<DirectionalLightComponent>().Color = { 1.0f, 0.89f, 0.96f };
				Firebox::Renderer3D::SetDirectionalLight(directionalLightEntity.GetComponent<DirectionalLightComponent>());
			}

			if (ImGui::MenuItem("Skybox"))
			{
				Firebox::Entity skyboxEntity = scene->CreateEntity("Skybox");
				Ref<Firebox::Skybox> skybox = CreateRef<Firebox::Skybox>();
				m_Context.SetSelectedEntity(skyboxEntity);
				skyboxEntity.AddComponent<SkyboxComponent>(skybox);
			}

			ImGui::EndMenu();
		}
		ImGui::EndPopup();
	}
	ImGui::PopStyleVar(2);
	ImGui::End();
	ImGui::PopStyleVar(3);
}


