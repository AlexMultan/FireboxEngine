#include "Debugger.h"
#include "Engine/Core/Log.h"

#include "imgui.h"
#include <string>

FireboxEditor::Debugger::Debugger()
{

}

FireboxEditor::Debugger::~Debugger()
{

}

void FireboxEditor::Debugger::RenderPanel()
{
	ImGui::Begin("Debugger");

	ImGui::Text("Stack Size: ");
	ImGui::SameLine();
	std::string stackSize = std::to_string(Firebox::Log::GetStackSize());
	ImGui::Text(stackSize.c_str());

	ImGui::End();
}
