#define IMGUI_DEFINE_MATH_OPERATORS
#include "UI/FloatParameters.h"
#include "Utils/String.h"
#include "Core/EditorUtils.h"

#include "imgui_internal.h"

void EditorUI::FloatParameters::Float3(Vector3* otherVector, const char* label)
{
	ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0.0f, 0.0f));

	if (ImGui::BeginTable("Parameters Row", 4))
	{
		ImGui::TableNextColumn();
		ImGui::Text(label);

		ImGui::TableNextColumn();
		DrawParameter("X", label, Vector4(0.611f, 0.0f, 0.0f, 1.0f), &otherVector->x);
		ImGui::TableNextColumn();
		DrawParameter("Y", label, Vector4(0.02f, 0.58f, 0.0f, 1.0f), &otherVector->y);
		ImGui::TableNextColumn();
		DrawParameter("Z", label, Vector4(0.0f, 0.466f, 1.0f, 1.0f), &otherVector->z);
		ImGui::EndTable();
	}

	ImGui::PopStyleVar();
}

void EditorUI::FloatParameters::DrawParameter(const char* text, const char* groupLabel, Vector4 color, float* parameter)
{
	ImVec2 pos = ImGui::GetCursorScreenPos();
	ImVec2 size = ImGui::CalcTextSize(text);

	/*ImVec4 base = ImGui::ColorConvertU32ToFloat4(IM_COL32(color.r * 255, color.g * 255, color.b * 255, color.a * 255));
	ImVec4 top = base * ImVec4(1.5f, 1.5f, 1.5f, 1.0f);
	ImVec4 bottom = base * ImVec4(0.45f, 0.45f, 0.45f, 1.0f);
	top.w = bottom.w = base.w;

	ImU32 col_top = ImGui::GetColorU32(top);
	ImU32 col_bot = ImGui::GetColorU32(bottom);*/

	float frameHeight = ImGui::GetFrameHeight();
	float paddingX = ImGui::GetStyle().ItemInnerSpacing.x;
	ImVec2 minPos = ImVec2(pos.x - paddingX, pos.y);
	ImVec2 maxPos = ImVec2(pos.x + size.x + paddingX, pos.y + frameHeight);

	ImDrawList* drawList = ImGui::GetWindowDrawList();
	drawList->AddRectFilled(minPos, maxPos, IM_COL32(color.r * 255, color.g * 255, color.b * 255, color.a * 255));
	ImGui::PushFont(FireboxEditor::EditorUtils::GetTransformAxesFont());
	ImGui::Text("%s", text);
	ImGui::PopFont();

	ImGui::SameLine(0.0f, paddingX);

	char id[64];
	snprintf(id, sizeof(id), "##%s_%s", groupLabel, text);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.86f, 0.86f, 0.86f, 1.0f));
	ImGui::PushFont(FireboxEditor::EditorUtils::GetTransformValuesFont());
	ImGui::DragFloat(id, parameter, 0.05f, -99999999.0f, 99999999.0f);
	ImGui::PopStyleColor();
	ImGui::PopFont();
}
