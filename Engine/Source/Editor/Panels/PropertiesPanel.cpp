#include "PropertiesPanel.h"
#include "UI/FloatParameters.h"
#include "Utils/DebugTools.h"
#include "Components/CoreComponents.h"
#include "Components/RenderComponents.h"
#include "Components/LightComponents.h"
#include "Scene/Entity.h"
#include "UI/ImGuiHelpers.h"
#include "Editor/EnginePaths.h"
#include "Rendering/Renderer3D.h"
#include "Core/EditorUtils.h"
#include "UI/MaterialEditor.h"

#include <imgui.h>

FireboxEditor::PropertiesPanel::PropertiesPanel(const char* name, EditorContext& context) : m_Name(name), m_Context(context)
{
	m_Context.AddEntitySelectionListener([this](Firebox::Entity newEntity)
		{
			m_SelectedEntity = newEntity;
		});
}

FireboxEditor::PropertiesPanel::~PropertiesPanel()
{

}

void FireboxEditor::PropertiesPanel::RenderPanel()
{
	static bool s_ShowMaterialEditor = false;
	ImGuiTreeNodeFlags defaultFlags = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_DefaultOpen;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 6.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

	ImGui::Begin(m_Name.c_str());

	if (m_SelectedEntity)
	{
		ImGui::Dummy(ImVec2(0.0f, 3.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(50.0f, 4.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
		if (ImGui::ButtonCenteredOnLine("Add Component", 0.5f))
		{
			ImGui::OpenPopup("AddComponentPopup");
		}
		ImGui::PopStyleVar(3);
		ImGui::Dummy(ImVec2(0.0f, 3.0f));

		ImGuiWindowFlags popupFlags = ImGuiWindowFlags_NoMove;

		if (ImGui::BeginPopup("AddComponentPopup", popupFlags))
		{
			if (ImGui::Button("Material"))
			{
				
			}
			ImGui::EndPopup();
		}

		if (m_SelectedEntity.HasComponent<TransformComponent>())
		{
			PushTreeNodeStyle();

			bool transformTree = ImGui::TreeNodeEx("Transform", defaultFlags);

			PopTreeNodeStyle();

			if (transformTree)
			{
				EditorUI::FloatParameters::Float3(&m_SelectedEntity.GetComponent<TransformComponent>().Position, "Location");
				EditorUI::FloatParameters::Float3(&m_SelectedEntity.GetComponent<TransformComponent>().Rotation, "Rotation");
				EditorUI::FloatParameters::Float3(&m_SelectedEntity.GetComponent<TransformComponent>().Scale, "Scale");
				ImGui::TreePop();
			}
		}

		if (m_SelectedEntity.HasComponent<StaticMeshComponent>())
		{
			PushTreeNodeStyle();

			bool staticMeshTree = ImGui::TreeNodeEx("Static Mesh", defaultFlags);

			PopTreeNodeStyle();

			if (staticMeshTree)
			{

				ImGui::Image((ImTextureID)(uintptr_t)FireboxEditor::EditorUtils::GetMeshIcon(),
					{ 64.0f, 64.0f }, ImVec2(0, 1), ImVec2(1, 0));
				ImGui::TreePop();
			}

			PushTreeNodeStyle();

			bool materialTree = ImGui::TreeNodeEx("Material", defaultFlags);

			PopTreeNodeStyle();

			if (materialTree)
			{
				auto& smc = m_SelectedEntity.GetComponent<StaticMeshComponent>();
				size_t matIndex = 0;
				for (size_t i = 0; i < smc.StaticMesh->GetMaterials().size(); i++)
				{
					ImGui::ImageButton(std::to_string(i).c_str(), (ImTextureID)(uintptr_t)smc.StaticMesh->GetMaterials()[i]->GetDiffuse()->GetTextureID(),
						{ 64.0f, 64.0f }, ImVec2(0, 1), ImVec2(1, 0));

					if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
					{
						s_ShowMaterialEditor = true;
						matIndex = i;
					}
				}
				MaterialEditor::DrawMaterialEditor(s_ShowMaterialEditor, smc.StaticMesh->GetMaterials()[matIndex]);
				ImGui::TreePop();
			}
		}

		if (m_SelectedEntity.HasComponent<MaterialComponent>())
		{
			PushTreeNodeStyle();

			bool materialTree = ImGui::TreeNodeEx("Material", defaultFlags);

			PopTreeNodeStyle();

			if (materialTree)
			{
				auto& mat = m_SelectedEntity.GetComponent<MaterialComponent>();
				ImGui::Image((ImTextureID)(uintptr_t)mat.Material->GetDiffuse()->GetTextureID(),
					{ 64.0f, 64.0f }, ImVec2(0, 1), ImVec2(1, 0));
				ImGui::TreePop();
			}
		}

		if (m_SelectedEntity.HasComponent<DirectionalLightComponent>())
		{
			PushTreeNodeStyle();

			bool dirLightTree = ImGui::TreeNodeEx("Directional Light", defaultFlags);

			PopTreeNodeStyle();

			if (dirLightTree)
			{
				EditorUI::FloatParameters::Float3(&m_SelectedEntity.GetComponent<DirectionalLightComponent>().Direction, "Direction");
				EditorUI::FloatParameters::Float3(&m_SelectedEntity.GetComponent<DirectionalLightComponent>().Color, "Color");
				Firebox::Renderer3D::SetDirectionalLight(m_SelectedEntity.GetComponent<DirectionalLightComponent>());
				ImGui::TreePop();
			}
		}

		if (m_SelectedEntity.HasComponent<SkyboxComponent>())
		{
			PushTreeNodeStyle();

			bool skyboxTree = ImGui::TreeNodeEx("Skybox", defaultFlags);

			PopTreeNodeStyle();

			if (skyboxTree)
			{
				ImGui::TreePop();
			}
		}

		if (m_SelectedEntity.HasComponent<PostProcessComponent>())
		{
			PushTreeNodeStyle();

			bool postProcessTree = ImGui::TreeNodeEx("Post Processing", defaultFlags);

			PopTreeNodeStyle();

			if (postProcessTree)
			{
				ImGui::DragFloat("Gamma", &m_Context.GetSelectedEntity().GetComponent<PostProcessComponent>().Gamma, 0.05f);
				Firebox::Renderer3D::SetPostProcessSettings(m_Context.GetSelectedEntity().GetComponent<PostProcessComponent>());
				ImGui::TreePop();
			}
		}
	}
	else
	{
		ImGui::Dummy({ 0.0f, 4.0f });
		ImGui::TextDisabledCenteredOnLine("Select any entity to view details", 0.5f, 1.15f);
	}

	ImGui::End();
	ImGui::PopStyleVar(2);
}

void FireboxEditor::PropertiesPanel::SetDragStrangth(const float& strength)
{
	m_DragStrength = strength;
}

void FireboxEditor::PropertiesPanel::PushTreeNodeStyle()
{
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4.0f, 2.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 7.0f));
}

void FireboxEditor::PropertiesPanel::PopTreeNodeStyle()
{
	ImGui::PopStyleVar(2);
}


