#include "ViewportPanel.h"
#include "Engine/Core/Application.h"
#include "Engine/Input/Input.h"
#include "Engine/Core/Log.h"
#include "Engine/Utils/DebugTools.h"
#include "Engine/Utils/String.h"

#include <imgui.h>
#include <ImGuizmo.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

#include <stdlib.h>

FireboxEditor::ViewportPanel::ViewportPanel(const char* name, EditorContext& context) : m_Name(name), m_Context(context), m_TextureID(0)
{
	
}

FireboxEditor::ViewportPanel::~ViewportPanel()
{

}

void FireboxEditor::ViewportPanel::RenderViewport(const Ref<Firebox::Framebuffer>& framebuffer, const Mat4& viewMatrix, const Mat4& projectionMatrix)
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::SetNextWindowBgAlpha(0.0f);

	ImGui::Begin("Viewport");

	Vector2 size = { ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y };

	uint texID = framebuffer->GetColorAttachment();
	ImGui::Image((ImTextureID)(uintptr_t)texID, { m_ViewportSize.x, m_ViewportSize.y }, ImVec2(0, 1), ImVec2(1, 0));

	if (size.x > 0.0f && size.y > 0.0f && (size.x != m_ViewportSize.x || size.y != m_ViewportSize.y))
	{
		m_ViewportSize = Vector2(size.x, size.y);
		framebuffer->ResizeFramebuffer(size.x, size.y);
	}

	m_IsFocused = ImGui::IsWindowHovered();

	Firebox::Entity entity = m_Context.selectedEntity;

	if (entity && entity.HasComponent<TransformComponent>())
	{
		ImGuizmo::SetOrthographic(false);
		ImGuizmo::SetDrawlist();
		ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, m_ViewportSize.x, m_ViewportSize.y);

		Mat4 transform = entity.GetComponent<TransformComponent>().GetTransform();

		if (ImGui::IsWindowFocused() || m_IsFocused)
		{
			if (Firebox::Input::IsKeyClicked(Firebox::FBK_KEY_W))
				m_GizmoTransformType = GizmoTransformType::Translate;
			if (Firebox::Input::IsKeyClicked(Firebox::FBK_KEY_E))
				m_GizmoTransformType = GizmoTransformType::Rotate;
			if (Firebox::Input::IsKeyClicked(Firebox::FBK_KEY_R))
				m_GizmoTransformType = GizmoTransformType::Scale;

			if (Firebox::Input::IsKeyClicked(Firebox::FBK_KEY_SPACE))
				m_GizmoTransformType = static_cast<GizmoTransformType>((static_cast<int>(m_GizmoTransformType) + 1) % 3);
		}

		ImGuizmo::OPERATION operation = ImGuizmo::OPERATION::TRANSLATE;
		ImGuizmo::MODE mode = ImGuizmo::WORLD;

		switch (m_GizmoTransformType)
		{
		case GizmoTransformType::Translate:
			operation = ImGuizmo::OPERATION::TRANSLATE;
			break;
		case GizmoTransformType::Rotate:
			operation = ImGuizmo::OPERATION::ROTATE;
			break;
		case GizmoTransformType::Scale:
			operation = ImGuizmo::OPERATION::SCALE;
			mode = ImGuizmo::LOCAL;
			break;
		default:
			break;
		}

		float gizmoSnapValues[3] = { m_GridSize * 0.1f, m_GridSize * 0.1f, m_GridSize * 0.1f };

		if (ImGuizmo::Manipulate(glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix), operation,
			mode, glm::value_ptr(transform), nullptr, m_Snap ? gizmoSnapValues : nullptr));
		{
			float translation[3], rotation[3], scale[3];
			ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(transform), translation, rotation, scale);

			entity.GetComponent<TransformComponent>().Position = Vector3(translation[0], translation[1], translation[2]);
			entity.GetComponent<TransformComponent>().Rotation = Vector3(rotation[0], rotation[1], rotation[2]);
			entity.GetComponent<TransformComponent>().Scale = Vector3(scale[0], scale[1], scale[2]);
		}
	}
		
	ImVec2 CameraSettingsPos{ m_ViewportSize.x - 70.0f, 30.0f };
	ImGui::SetNextItemAllowOverlap();
	ImGui::SetCursorPos(CameraSettingsPos);
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4.0f);
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.6f, 0.6f, 0.6f, 0.4f));
	if (ImGui::Button("Camera"))
	{
		ImGui::OpenPopup("CameraSettingsPopup");
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();

	ImGuiWindowFlags popupFlags = ImGuiWindowFlags_NoMove;
	if (ImGui::BeginPopup("CameraSettingsPopup", popupFlags))
	{
		ImGui::TextDisabled("Camera Settings");
		ImGui::Separator();
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.9f, 0.9f, 0.9f, 1.0f));
		ImGui::SliderFloat("Camera Speed", &m_CameraSpeed, 2.0f, 50.0f, "%.1f");
		ImGui::Separator();
		ImGui::Checkbox("Snap", &m_Snap);
		ImGui::Separator();
		static const char* snapValues[]{ "1", "5", "10", "50", "100"};
		static int selectedValue = 2;
		if (ImGui::Combo("Snap Size", &selectedValue, snapValues, IM_ARRAYSIZE(snapValues)))
		{
			FB_CONSOLE_PRINT(Utils::ToString(selectedValue));
			float gridSize = atof(snapValues[selectedValue]);
			m_GridSize = gridSize / 10.0f;
		}
		ImGui::PopStyleColor();
		ImGui::EndPopup();
	}

	ImVec2 RenderingSettingsPos{ CameraSettingsPos.x - 80.0f, CameraSettingsPos.y };
	ImGui::SetNextItemAllowOverlap();
	ImGui::SetCursorPos(RenderingSettingsPos);
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4.0f);
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.6f, 0.6f, 0.6f, 0.4f));
	if (ImGui::Button("Rendering"))
	{
		ImGui::OpenPopup("RenderingSettingsPopup");
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();

	if (ImGui::BeginPopup("RenderingSettingsPopup", popupFlags))
	{
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.9f, 0.9f, 0.9f, 1.0f));
		static const char* viewModes[]{ "Lit", "Unlit", "Depth" };
		static int selectedMode = 0;
		if (ImGui::Combo("View Mode", &selectedMode, viewModes, IM_ARRAYSIZE(viewModes)))
		{
			FB_CONSOLE_PRINT(Utils::ToString(selectedMode));
			m_CurrentViewMode = selectedMode;
		}
		ImGui::PopStyleColor();
		ImGui::EndPopup();
	}

	ImGui::End();

	ImGui::PopStyleVar();
}
