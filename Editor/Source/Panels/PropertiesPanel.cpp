#include "PropertiesPanel.h"
#include "UI/FloatParameters.h"
#include "Utils/DebugTools.h"
#include "Components/CoreComponents.h"
#include "Components/RenderComponents.h"
#include "Components/LightComponents.h"
#include "Scene/Entity.h"
#include "UI/ImGuiHelpers.h"
#include "Editor/EngineAssets.h"
#include "Rendering/Renderer3D.h"
#include "Core/EditorUtils.h"
#include "UI/MaterialEditor.h"

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
	static bool s_ShowMaterialEditor = false;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 6.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::Begin(m_Name.c_str());

	if (entity)
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

		if (entity.HasComponent<DirectionalLightComponent>() && m_TransformPropertiesFont)
		{
			EditorUI::FloatParameters::Float3(&entity.GetComponent<DirectionalLightComponent>().Direction, "Light Dir", m_TransformPropertiesFont);
		}

		if (entity.HasComponent<TransformComponent>() && m_TransformPropertiesFont)
		{
			PushTreeNodeStyle();

			ImGuiTreeNodeFlags transformTreeFlags = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_DefaultOpen;
			bool transformTree = ImGui::TreeNodeEx("Transform", transformTreeFlags);

			PopTreeNodeStyle();

			if (transformTree)
			{
				EditorUI::FloatParameters::Float3(&entity.GetComponent<TransformComponent>().Position, "Location", m_TransformPropertiesFont);
				EditorUI::FloatParameters::Float3(&entity.GetComponent<TransformComponent>().Rotation, "Rotation", m_TransformPropertiesFont);
				EditorUI::FloatParameters::Float3(&entity.GetComponent<TransformComponent>().Scale, "Scale", m_TransformPropertiesFont);
				ImGui::TreePop();
			}
		}

		if (entity.HasComponent<StaticMeshComponent>())
		{
			PushTreeNodeStyle();

			ImGuiTreeNodeFlags staticMeshTreeFlags = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_DefaultOpen;
			bool staticMeshTree = ImGui::TreeNodeEx("Static Mesh", staticMeshTreeFlags);

			PopTreeNodeStyle();

			if (staticMeshTree)
			{

				ImGui::Image((ImTextureID)(uintptr_t)FireboxEditor::EditorUtils::GetMeshIconTexture(),
					{ 64.0f, 64.0f }, ImVec2(0, 1), ImVec2(1, 0));
				ImGui::TreePop();
			}

			PushTreeNodeStyle();

			ImGuiTreeNodeFlags materialTreeFlags = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_DefaultOpen;
			bool materialTree = ImGui::TreeNodeEx("Material", materialTreeFlags);

			PopTreeNodeStyle();

			if (materialTree)
			{
				auto& smc = entity.GetComponent<StaticMeshComponent>();
				for (size_t i = 0; i < smc.StaticMesh->GetMaterials().size(); i++)
				{
					ImGui::Image((ImTextureID)(uintptr_t)smc.StaticMesh->GetMaterials()[i]->GetDiffuse()->GetTextureID(), 
						{64.0f, 64.0f}, ImVec2(0, 1), ImVec2(1, 0));

					MaterialEditor::DrawMaterialEditor(s_ShowMaterialEditor, smc.StaticMesh->GetMaterials()[i]);

					if (ImGui::Button("Edit Material"))
					{
						s_ShowMaterialEditor = true;
					}
				}

				ImGui::TreePop();
			}
		}

		if (entity.HasComponent<MaterialComponent>())
		{
			PushTreeNodeStyle();

			ImGuiTreeNodeFlags materialTreeFlags = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_DefaultOpen;
			bool materialTree = ImGui::TreeNodeEx("Material", materialTreeFlags);

			PopTreeNodeStyle();

			if (materialTree)
			{
				auto& mat = entity.GetComponent<MaterialComponent>();
				ImGui::Image((ImTextureID)(uintptr_t)mat.Material->GetDiffuse()->GetTextureID(),
					{ 64.0f, 64.0f }, ImVec2(0, 1), ImVec2(1, 0));
				ImGui::TreePop();
			}
		}

		if (entity.HasComponent<SkyboxComponent>())
		{
			PushTreeNodeStyle();

			ImGuiTreeNodeFlags skyboxTreeFlags = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_DefaultOpen;
			bool skyboxTree = ImGui::TreeNodeEx("Skybox", skyboxTreeFlags);

			PopTreeNodeStyle();

			if (skyboxTree)
			{
				ImGui::TreePop();
			}
		}
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


