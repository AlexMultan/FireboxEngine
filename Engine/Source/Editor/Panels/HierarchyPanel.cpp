#include "HierarchyPanel.h"
#include "UI/EntityHierarchyNode.h"
#include "Scene/Entity.h"
#include "Components/CoreComponents.h"
#include "Components/RenderComponents.h"
#include "Rendering/Geometry/PrimitiveShapes.h"
#include "Rendering/Renderer3D.h"
#include "Editor/EditorPaths.h"

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
	const char* sceneName = scene->GetSceneName().c_str();
	if (ImGui::TreeNodeEx(sceneName, hierarchyNodeFlags))
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

			if (ImGui::BeginMenu("3D Objects"))
			{
				if (ImGui::MenuItem("Plane"))
				{
					Firebox::Entity planeEntity = scene->CreateEntity("Plane");
					m_Context.SetSelectedEntity(planeEntity);
					Ref<Firebox::StaticMesh> planeMesh = CreateRef<Firebox::StaticMesh>(FireboxEditor::EditorContent::Get("Models/SM_Plane.glb").string());
					planeEntity.AddComponent<StaticMeshComponent>(planeMesh);
				}

				if (ImGui::MenuItem("Cube"))
				{
					Firebox::Entity cubeEntity = scene->CreateEntity("Cube");
					m_Context.SetSelectedEntity(cubeEntity);
					Ref<Firebox::StaticMesh> cubeMesh = CreateRef<Firebox::StaticMesh>(FireboxEditor::EditorContent::Get("Models/SM_Cube.glb").string());
					cubeEntity.AddComponent<StaticMeshComponent>(cubeMesh);
				}

				if (ImGui::MenuItem("Sphere"))
				{
					Firebox::Entity sphereEntity = scene->CreateEntity("Sphere");
					m_Context.SetSelectedEntity(sphereEntity);
					Ref<Firebox::StaticMesh> sphereMesh = CreateRef<Firebox::StaticMesh>(FireboxEditor::EditorContent::Get("Models/SM_Sphere.glb").string());
					sphereEntity.AddComponent<StaticMeshComponent>(sphereMesh);
				}

				if (ImGui::MenuItem("Cylinder"))
				{
					Firebox::Entity cylinderEntity = scene->CreateEntity("Cylinder");
					m_Context.SetSelectedEntity(cylinderEntity);
					Ref<Firebox::StaticMesh> cylinderMesh = CreateRef<Firebox::StaticMesh>(FireboxEditor::EditorContent::Get("Models/SM_Cylinder.glb").string());
					cylinderEntity.AddComponent<StaticMeshComponent>(cylinderMesh);
				}

				if (ImGui::MenuItem("Cone"))
				{
					Firebox::Entity coneEntity = scene->CreateEntity("Cone");
					m_Context.SetSelectedEntity(coneEntity);
					Ref<Firebox::StaticMesh> coneMesh = CreateRef<Firebox::StaticMesh>(FireboxEditor::EditorContent::Get("Models/SM_Cone.glb").string());
					coneEntity.AddComponent<StaticMeshComponent>(coneMesh);
				}

				if (ImGui::MenuItem("Monkey"))
				{
					Firebox::Entity monkeyEntity = scene->CreateEntity("Monkey");
					m_Context.SetSelectedEntity(monkeyEntity);
					Ref<Firebox::StaticMesh> monkeyMesh = CreateRef<Firebox::StaticMesh>(FireboxEditor::EditorContent::Get("Models/SM_Monkey.glb").string());
					monkeyEntity.AddComponent<StaticMeshComponent>(monkeyMesh);
				}
				ImGui::EndMenu();
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

			if (ImGui::MenuItem("Point Light"))
			{
				Firebox::Entity pointLightEntity = scene->CreateEntity("Point Light");
				m_Context.SetSelectedEntity(pointLightEntity);
				pointLightEntity.AddComponent<PointLightComponent>();
				Firebox::Renderer3D::GetPointLights().emplace_back(pointLightEntity.GetComponent<PointLightComponent>());
			}

			if (ImGui::MenuItem("Spot Light"))
			{
				Firebox::Entity spotLightEntity = scene->CreateEntity("Spot Light");
				m_Context.SetSelectedEntity(spotLightEntity);
				spotLightEntity.AddComponent<SpotLightComponent>();
				Firebox::Renderer3D::GetSpotLights().emplace_back(spotLightEntity.GetComponent<SpotLightComponent>());
			}

			if (ImGui::MenuItem("Skybox"))
			{
				Firebox::Entity skyboxEntity = scene->CreateEntity("Skybox");
				Ref<Firebox::Skybox> skybox = CreateRef<Firebox::Skybox>();
				m_Context.SetSelectedEntity(skyboxEntity);
				skyboxEntity.AddComponent<SkyboxComponent>(skybox);
			}

			if (ImGui::MenuItem("Post Process Volume"))
			{
				Firebox::Entity postProcessEnitity = scene->CreateEntity("Post Process Volume");
				m_Context.SetSelectedEntity(postProcessEnitity);
				postProcessEnitity.AddComponent<PostProcessComponent>();
			}

			ImGui::EndMenu();
		}
		ImGui::EndPopup();
	}
	ImGui::PopStyleVar(2);
	ImGui::End();
	ImGui::PopStyleVar(3);
}


