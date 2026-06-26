#include "EntityOutlinerNode.h"
#include "Engine/Core/Log.h"

#include <imgui.h>

bool FireboxEditor::EntityOutlinerNode::DrawNode(const char* name, const uint64 id, bool isSelected)
{
	ImGuiTreeNodeFlags entityNodeFlags = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_OpenOnArrow;

	if (!isSelected)
	{
		ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.09f, 0.09f, 0.09f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.12f, 0.12f, 0.12f, 1.00f));
	}
	else
	{
		ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.29f, 0.47f, 0.85f, 1.00f));
		ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.31f, 0.53f, 0.98f, 1.00f));
	}

	ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.29f, 0.47f, 0.85f, 1.00f));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(3.0f, 2.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));		

	bool entityNode = ImGui::TreeNodeEx((void*)(uintptr_t)id, entityNodeFlags, name);

	ImGui::PopStyleColor(3);
	ImGui::PopStyleVar(2);

	bool wasClicked = ImGui::IsItemClicked(ImGuiMouseButton_Left);

	if (entityNode)
		ImGui::TreePop();

	return wasClicked;
}
