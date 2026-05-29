#include "Editor/UI/FloatParameters.h"
#include "Engine/Utils/String.h"

#include <imgui.h>

void FireboxEditor::FloatParameters::Float3(Vector3* otherVector, const char* label)
{
	ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0.0f, 0.0f));

	if (ImGui::BeginTable("Parameters Row", 4))
	{
		ImGui::TableNextColumn();
		ImGui::Text(label);

		ImGui::TableNextColumn();
		DrawParameter("X", label, Vector4(1.0f, 0.0f, 0.0f, 1.0f), &otherVector->x);
		ImGui::TableNextColumn();
		DrawParameter("Y", label, Vector4(0.164f, 0.658f, 0.0f, 1.0f), &otherVector->y);
		ImGui::TableNextColumn();
		DrawParameter("Z", label, Vector4(0.0f, 0.466f, 1.0f, 1.0f), &otherVector->z);
		ImGui::EndTable();
	}

	ImGui::PopStyleVar();
}

void FireboxEditor::FloatParameters::DrawParameter(const char* text, const char* groupLabel, Vector4 color, float* parameter)
{
	ImVec2 pos = ImGui::GetCursorScreenPos();
	ImVec2 size = ImGui::CalcTextSize(text);

	float frameHeight = ImGui::GetFrameHeight();
	float paddingX = 3.0f;
	ImVec2 minPos = ImVec2(pos.x - paddingX, pos.y);
	ImVec2 maxPos = ImVec2(pos.x + size.x + paddingX, pos.y + frameHeight);

	ImDrawList* drawList = ImGui::GetWindowDrawList();
	drawList->AddRectFilled(minPos, maxPos, IM_COL32(color.r * 255, color.g * 255, color.b * 255, color.a * 255));

	ImGui::Text("%s", text);

	ImGui::SameLine(0.0f, paddingX);

	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.09f, 0.09f, 0.09f, 1.0f));
	char id[64];
	snprintf(id, sizeof(id), "##%s_%s", groupLabel, text);
	ImGui::DragFloat(id, parameter, 0.05f, -99999999.0f, 99999999.0f);
	ImGui::PopStyleColor();
}
