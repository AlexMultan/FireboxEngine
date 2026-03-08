#include "ViewportPanel.h"
#include "Engine/Core/Application.h"

#include "imgui.h"

FireboxEditor::ViewportPanel::ViewportPanel()
{

}

FireboxEditor::ViewportPanel::ViewportPanel(const char* name, uint textureID) : m_Name(name), m_TextureID(textureID)
{

}

FireboxEditor::ViewportPanel::~ViewportPanel()
{

}

void FireboxEditor::ViewportPanel::RenderPanel()
{
	ImGui::Begin("Viewport"); // Viewport Begin

	Vector2 size = Vector2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y);

	if (size.x != m_ViewportSize.x || size.y != m_ViewportSize.y)
	{
		m_ViewportSize = Vector2(size.x, size.y);
		Firebox::Application::Get().GetRenderer2D().GetRendererAPI()->ResizeFramebuffer(size.x, size.y);
	}

	ImGui::Image((ImTextureID)m_TextureID, ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));
	m_ViewportSize = Vector2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y);
	Firebox::Application::Get().GetRenderer2D().GetRendererAPI()->SetViewportSize(m_ViewportSize);

	ImGui::End(); // Viewport End
}
