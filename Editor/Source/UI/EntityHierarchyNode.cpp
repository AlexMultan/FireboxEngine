#include "EntityHierarchyNode.h"
#include "Core/Log.h"
#include "Core/EditorUtils.h"

#include <imgui.h>

bool EditorUI::EntityHierarchyNode::DrawNode(const char* name, const uint64 id, bool isSelected)
{
	ImGuiTreeNodeFlags entityNodeFlags = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_Leaf;

	if (isSelected)
	{
		ImGui::PushFont(FireboxEditor::EditorUtils::GetSelectedEntityNodeFont());
		ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.29f, 0.47f, 0.85f, 1.00f));
		ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.31f, 0.53f, 0.98f, 1.00f));
	}

	ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.29f, 0.47f, 0.85f, 1.00f));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20.0f, 3.0f));	
	ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);	

	bool entityNode = ImGui::TreeNodeEx((void*)(uintptr_t)id, entityNodeFlags, name);

	if (isSelected)
	{
		ImGui::PopStyleColor(3);
		ImGui::PopFont();
	}
	else
		ImGui::PopStyleColor(1);

	ImGui::PopStyleVar(2);

	bool wasClicked = ImGui::IsItemClicked(ImGuiMouseButton_Left);

	if (entityNode)
		ImGui::TreePop();

	return wasClicked;
}
