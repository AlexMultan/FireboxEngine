#include "ViewportPanel.h"
#include "Engine/Core/Application.h"
#include "Engine/Input/Input.h"
#include "Engine/Core/Log.h"

#include <imgui.h>

FireboxEditor::ViewportPanel::ViewportPanel()
{

}

FireboxEditor::ViewportPanel::ViewportPanel(const char* name) : m_Name(name)
{
	
}

FireboxEditor::ViewportPanel::~ViewportPanel()
{

}

void FireboxEditor::ViewportPanel::RenderViewport(const Ref<Firebox::Framebuffer>& framebuffer)
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

	if (Utils::InRange(ImGui::GetMousePos().x, 0.0f, m_ViewportSize.x) && Utils::InRange(ImGui::GetMousePos().y, 0.0f, m_ViewportSize.y))
	{
		m_IsFocused = true;
	}
	else
	{
		m_IsFocused = false;
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
