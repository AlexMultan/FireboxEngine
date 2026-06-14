#include "ViewportPanel.h"
#include "Engine/Core/Application.h"
#include "Engine/Input/Input.h"
#include "Engine/Core/Log.h"

#include <imgui.h>
#include <ImGuizmo.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

FireboxEditor::ViewportPanel::ViewportPanel()
{

}

FireboxEditor::ViewportPanel::ViewportPanel(const char* name) : m_Name(name)
{
	
}

FireboxEditor::ViewportPanel::~ViewportPanel()
{

}

void FireboxEditor::ViewportPanel::RenderViewport(const Ref<Firebox::Framebuffer>& framebuffer, const Mat4& viewMatrix, const Mat4& projectionMatrix,
	TransformComponent& transformComp)
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	
	ImGui::SetNextWindowBgAlpha(0.0f);

	ImGui::Begin("Viewport"); // Viewport Begin
	Vector2 size = { ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y };

	uint texID = framebuffer->GetColorAttachment();
	ImGui::Image((ImTextureID)(uintptr_t)texID, { m_ViewportSize.x, m_ViewportSize.y }, ImVec2(0, 1), ImVec2(1, 0));

	if (size.x > 0.0f && size.y > 0.0f && (size.x != m_ViewportSize.x || size.y != m_ViewportSize.y))
	{
		m_ViewportSize = Vector2(size.x, size.y);
		framebuffer->ResizeFramebuffer(size.x, size.y);
	}

	m_IsFocused = ImGui::IsWindowHovered();

	ImGuizmo::SetOrthographic(false);
	ImGuizmo::SetDrawlist();
	ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, m_ViewportSize.x, m_ViewportSize.y);

	Mat4 transform = transformComp.GetTransform();

	if (ImGui::IsWindowFocused() || m_IsFocused)
	{
		if (Firebox::Input::IsKeyClicked(Firebox::FBK_KEY_W))
			m_GizmoTransformType = GizmoTransformType::Translate;
		if (Firebox::Input::IsKeyClicked(Firebox::FBK_KEY_E))
			m_GizmoTransformType = GizmoTransformType::Rotate;
		if (Firebox::Input::IsKeyClicked(Firebox::FBK_KEY_R))
			m_GizmoTransformType = GizmoTransformType::Scale;

		if(Firebox::Input::IsKeyClicked(Firebox::FBK_KEY_SPACE))
			m_GizmoTransformType = static_cast<GizmoTransformType>((static_cast<int>(m_GizmoTransformType) + 1) % 3);
	}

	ImGuizmo::OPERATION operation = ImGuizmo::OPERATION::TRANSLATE;
	
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
			break;
		default:
			break;
	}

	if (ImGuizmo::Manipulate(glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix), operation,
		ImGuizmo::WORLD, glm::value_ptr(transform)))
	{
		float translation[3], rotation[3], scale[3];
		ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(transform), translation, rotation, scale);

		transformComp.Position = Vector3(translation[0], translation[1], translation[2]);
		transformComp.Rotation = Vector3(rotation[0], rotation[1], rotation[2]);
		transformComp.Scale = Vector3(scale[0], scale[1], scale[2]);
	}
		

	ImGui::SetNextItemAllowOverlap();
	ImGui::SetCursorPos(ImVec2(m_ViewportSize.x - 70.0f, 30.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4.0f);
	if (ImGui::Button("Settings"))
	{
		ImGui::OpenPopup("ViewportSettingsPopup");
	}
	ImGui::PopStyleVar();

	ImGuiWindowFlags popupFlags = ImGuiWindowFlags_NoMove;
	if (ImGui::BeginPopup("ViewportSettingsPopup", popupFlags))
	{
		ImGui::TextDisabled("Camera Settings");
		ImGui::Separator();
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.9f, 0.9f, 0.9f, 1.0f));
		ImGui::SliderFloat("Camera Speed", &m_CameraSpeed, 2.0f, 50.0f, "%.1f");
		ImGui::PopStyleColor();
		ImGui::EndPopup();
	}

	ImGui::End(); // Viewport End

	ImGui::PopStyleVar(2);
}
