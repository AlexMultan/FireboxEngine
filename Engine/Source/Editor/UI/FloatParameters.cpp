#define IMGUI_DEFINE_MATH_OPERATORS
#include "UI/FloatParameters.h"
#include "Utils/String.h"
#include "Core/EditorUtils.h"

#include "imgui_internal.h"

void EditorUI::FloatParameters::Float1(float* otherFloat, const char* label)
{
	ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.0f);

	if (ImGui::BeginTable("Parameters Row", 2))
	{
		ImGui::TableNextColumn();
		static float leftWidth = 100.0f;
		float paneHeight = 40.0f;

		ImGui::BeginChild("LeftPane", ImVec2(leftWidth, paneHeight), true);
		ImGui::Text(label);
		ImGui::EndChild();
		ImGui::SameLine();

		ImGui::Button("##01", ImVec2(6.0f, paneHeight));
		if (ImGui::IsItemActive())
		{
			leftWidth += ImGui::GetIO().MouseDelta.x;
		}

		ImGui::SameLine();
		ImGui::BeginChild("RightPane", ImVec2(0, paneHeight), true);
		ImGui::TableNextColumn();
		DrawParameter("##", label, Vector4(0.611f, 0.0f, 0.0f, 1.0f), otherFloat, false);
		ImGui::EndChild();
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
		DrawParameter("X", label, Vector4(0.611f, 0.0f, 0.0f, 1.0f), &otherVector->x, true);
		ImGui::TableNextColumn();
		DrawParameter("Y", label, Vector4(0.02f, 0.58f, 0.0f, 1.0f), &otherVector->y, true);
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
		DrawParameter("X", label, Vector4(0.611f, 0.0f, 0.0f, 1.0f), &otherVector->x, true);
		ImGui::TableNextColumn();
		DrawParameter("Y", label, Vector4(0.02f, 0.58f, 0.0f, 1.0f), &otherVector->y, true);
		ImGui::TableNextColumn();
		DrawParameter("Z", label, Vector4(0.0f, 0.466f, 1.0f, 1.0f), &otherVector->z, true);
		ImGui::EndTable();
	}

	ImGui::PopStyleVar();
}

void EditorUI::FloatParameters::DrawParameter(const char* text, const char* groupLabel, Vector4 color, float* parameter, bool labelBox)
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
	ImGui::PushFont(FireboxEditor::EditorUtils::GetTransformValuesFont());
	ImGui::DragFloat(id, parameter, 0.05f, -99999999.0f, 99999999.0f);
	ImGui::PopStyleColor();
	ImGui::PopFont();
}
