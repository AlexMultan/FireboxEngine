#include "ConsolePanel.h"
#include "Engine/Utils/DebugTools.h"

#include "imgui.h"

FireboxEditor::ConsolePanel::ConsolePanel()
{

}

FireboxEditor::ConsolePanel::~ConsolePanel()
{

}

void FireboxEditor::ConsolePanel::RenderPanel()
{
	ImGui::Begin("Console"); // Console Panel Begin

	if (ImGui::Button("Clear Console"))
	{
		if (!Firebox::Console::GetMessages().empty())
		{
			Firebox::Console::ClearConsole();
		}
	}

	ImGui::Separator();

	if (!Firebox::Console::GetMessages().empty() && Firebox::Console::GetMessages().size() > 0)
	{
		for (String msg : Firebox::Console::GetMessages())
		{
			ImGui::Text(msg.c_str());
		}
	}
	
	ImGui::End(); // Console Panel End
}

