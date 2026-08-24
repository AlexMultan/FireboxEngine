#define IMGUI_DEFINE_MATH_OPERATORS
#include "UI/FloatParameters.h"
#include "Utils/String.h"
#include "Core/EditorUtils.h"

#include "imgui_internal.h"

void EditorUI::FloatParameters::Checkbox(bool* otherBool, const char* label)
{
	ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.0f);

	if (ImGui::BeginTable("Parameters Row", 2))
	{
		ImGui::TableNextColumn();
		ImGui::Text(label);
		ImGui::SameLine();

		ImGui::TableNextColumn();
		DrawCheckbox("##", label, Vector4(0.611f, 0.0f, 0.0f, 1.0f), otherBool);
		ImGui::EndTable();
	}

	ImGui::PopStyleVar(2);
}

// TODO: Move int parameters to other class or just leave it here and rename the file and the class.
void EditorUI::FloatParameters::Int1(int* otherInt, const char* label)
{
	ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.0f);

	if (ImGui::BeginTable("Parameters Row", 2))
	{
		ImGui::TableNextColumn();
		ImGui::Text(label);
		ImGui::SameLine();

		ImGui::TableNextColumn();
		DrawIntParameter("##", label, Vector4(0.611f, 0.0f, 0.0f, 1.0f), otherInt, false);
		ImGui::EndTable();
	}

	ImGui::PopStyleVar(2);
}

void EditorUI::FloatParameters::Float1(float* otherFloat, const char* label)
{
	ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.0f);

	if (ImGui::BeginTable("Parameters Row", 2))
	{
		ImGui::TableNextColumn();
		ImGui::Text(label);
		ImGui::SameLine();

		ImGui::TableNextColumn();
		DrawFloatParameter("##", label, Vector4(0.611f, 0.0f, 0.0f, 1.0f), otherFloat, false);
		ImGui::EndTable();
	}

	ImGui::PopStyleVar(2);
}

void EditorUI::FloatParameters::Float2(Vector2* otherVector, const char* label)
{
	ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0.0f, 0.0f));

	if (ImGui::BeginTable("Parameters Row", 3))
	{
		ImGui::TableNextColumn();
		ImGui::Text(label);

		ImGui::TableNextColumn();
		DrawFloatParameter("X", label, Vector4(0.611f, 0.0f, 0.0f, 1.0f), &otherVector->x, true);
		ImGui::TableNextColumn();
		DrawFloatParameter("Y", label, Vector4(0.02f, 0.58f, 0.0f, 1.0f), &otherVector->y, true);
		ImGui::EndTable();
	}

	ImGui::PopStyleVar();
}

void EditorUI::FloatParameters::Float3(Vector3* otherVector, const char* label)
{
	ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0.0f, 0.0f));

	if (ImGui::BeginTable("Parameters Row", 4))
	{
		ImGui::TableNextColumn();
		ImGui::Text(label);

		ImGui::TableNextColumn();
		DrawFloatParameter("X", label, Vector4(0.611f, 0.0f, 0.0f, 1.0f), &otherVector->x, true);
		ImGui::TableNextColumn();
		DrawFloatParameter("Y", label, Vector4(0.02f, 0.58f, 0.0f, 1.0f), &otherVector->y, true);
		ImGui::TableNextColumn();
		DrawFloatParameter("Z", label, Vector4(0.0f, 0.466f, 1.0f, 1.0f), &otherVector->z, true);
		ImGui::EndTable();
	}

	ImGui::PopStyleVar();
}

void EditorUI::FloatParameters::DrawFloatParameter(const char* text, const char* groupLabel, Vector4 color, float* parameter, bool labelBox)
{
	if (labelBox)
	{
		ImVec2 pos = ImGui::GetCursorScreenPos();
		ImVec2 size = ImGui::CalcTextSize(text);

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
	}
	
	char id[64];
	snprintf(id, sizeof(id), "##%s_%s", groupLabel, text);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.86f, 0.86f, 0.86f, 1.0f));
	//ImGui::PushFont(FireboxEditor::EditorUtils::GetTransformValuesFont());
	ImGui::DragFloat(id, parameter, 0.05f, -99999999.0f, 99999999.0f);
	ImGui::PopStyleColor();
	//ImGui::PopFont();
}

void EditorUI::FloatParameters::DrawIntParameter(const char* text, const char* groupLabel, Vector4 color, int* parameter, bool labelBox)
{
	if (labelBox)
	{
		ImVec2 pos = ImGui::GetCursorScreenPos();
		ImVec2 size = ImGui::CalcTextSize(text);

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
	}

	char id[64];
	snprintf(id, sizeof(id), "##%s_%s", groupLabel, text);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.86f, 0.86f, 0.86f, 1.0f));
	//ImGui::PushFont(FireboxEditor::EditorUtils::GetTransformValuesFont());
	ImGui::DragInt(id, parameter, 0.05f, -99999999, 99999999);
	ImGui::PopStyleColor();
	//ImGui::PopFont();
}

void EditorUI::FloatParameters::DrawCheckbox(const char* text, const char* groupLabel, Vector4 color, bool* parameter)
{
	char id[64];
	snprintf(id, sizeof(id), "##%s_%s", groupLabel, text);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.86f, 0.86f, 0.86f, 1.0f));
	ImGui::Checkbox(id, parameter);
	ImGui::PopStyleColor();
}
