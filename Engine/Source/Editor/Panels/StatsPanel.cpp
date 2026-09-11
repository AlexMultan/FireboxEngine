#include "StatsPanel.h"
#include "Utils/DebugTools.h"

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
	ImGui::Text("Frames per second: %.1f", ImGui::GetIO().Framerate);
	ImGui::Text("Application average %.3f ms/frame", 1000.0f / ImGui::GetIO().Framerate);
	ImGui::Text("Draw Calls: %d", Firebox::Console::GetDrawCalls());
	ImGui::Text("Vertices: %llu", static_cast<unsigned long long>(Firebox::Console::GetVertexCount()));
	ImGui::Text("Indices: %llu", static_cast<unsigned long long>(Firebox::Console::GetIndexCount()));
	ImGui::End();
}
