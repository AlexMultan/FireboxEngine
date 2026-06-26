#include "StatsPanel.h"
#include "Engine/Utils/DebugTools.h"

FireboxEditor::StatsPanel::StatsPanel()
{

}

FireboxEditor::StatsPanel::StatsPanel(const char* name) : m_Name(name)
{

}

FireboxEditor::StatsPanel::~StatsPanel()
{

}

void FireboxEditor::StatsPanel::RenderPanel()
{
	ImGui::Begin(m_Name.c_str());
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("Draw Calls: %d", Firebox::Console::GetDrawCalls());
	ImGui::End();
}
