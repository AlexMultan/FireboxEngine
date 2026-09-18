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
bool EditorUI::FloatParameters::Int1(int* otherInt, const char* label)
{
	bool changed = false;
	ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.0f);

	if (ImGui::BeginTable("Parameters Row", 2))
	{
		ImGui::TableNextColumn();
		ImGui::Text(label);
		ImGui::SameLine();

		ImGui::TableNextColumn();
		changed = DrawIntParameter("##", label, Vector4(0.611f, 0.0f, 0.0f, 1.0f), otherInt, false);
		ImGui::EndTable();
	}

	ImGui::PopStyleVar(2);
	return changed;
}

bool EditorUI::FloatParameters::Float1(float* otherFloat, const char* label)
{
	bool changed = false;
	ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.0f);

	if (ImGui::BeginTable("Parameters Row", 2))
	{
		ImGui::TableNextColumn();
		ImGui::Text(label);
		ImGui::SameLine();

		ImGui::TableNextColumn();
		changed = DrawFloatParameter("##", label, Vector4(0.611f, 0.0f, 0.0f, 1.0f), otherFloat, false);
		ImGui::EndTable();
	}

	ImGui::PopStyleVar(2);
	return changed;
}

bool EditorUI::FloatParameters::Float2(Vector2* otherVector, const char* label)
{
	static const char* componentLabels[2] = { "X", "Y" };
	return DrawFloatComponents(&otherVector->x, 2, componentLabels, label);
}

bool EditorUI::FloatParameters::Float3(Vector3* otherVector, const char* label)
{
	static const char* componentLabels[3] = { "X", "Y", "Z"};
	return DrawFloatComponents(&otherVector->x, 3, componentLabels, label);
}

bool EditorUI::FloatParameters::Float4(Vector4* otherVector, const char* label)
{
	static const char* componentLabels[4] = { "R", "G", "B", "A" };
	return DrawFloatComponents(&otherVector->r, 4, componentLabels, label);
}

bool EditorUI::FloatParameters::DrawFloatParameter(const char* text, const char* groupLabel, Vector4 color, float* parameter, bool labelBox)
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
	bool changed = ImGui::DragFloat(id, parameter, 0.05f, -99999999.0f, 99999999.0f);
	ImGui::PopStyleColor();

	return changed;
}

bool EditorUI::FloatParameters::DrawIntParameter(const char* text, const char* groupLabel, Vector4 color, int* parameter, bool labelBox)
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
	bool changed = ImGui::DragInt(id, parameter, 0.05f, -99999999, 99999999);
	ImGui::PopStyleColor();

	return changed;
}

void EditorUI::FloatParameters::DrawCheckbox(const char* text, const char* groupLabel, Vector4 color, bool* parameter)
{
	char id[64];
	snprintf(id, sizeof(id), "##%s_%s", groupLabel, text);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.86f, 0.86f, 0.86f, 1.0f));
	ImGui::Checkbox(id, parameter);
	ImGui::PopStyleColor();
}

bool EditorUI::FloatParameters::DrawFloatComponents(float* components, int count, const char* const* labels, const char* groupLabel)
{
    bool changed = false;

	ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0.0f, 0.0f));
	if (ImGui::BeginTable("Parameters Row", count + 1))
	{
		ImGui::TableNextColumn();
		ImGui::TextUnformatted(groupLabel);

		for (int i = 0; i < count; i++)
		{
			ImGui::TableNextColumn();
			changed |= DrawFloatParameter(labels[i], groupLabel, s_ComponentColors[i], &components[i], true);
		}

		ImGui::EndTable();
	}
	ImGui::PopStyleVar();
	return changed;
}
