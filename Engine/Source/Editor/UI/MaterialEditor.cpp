#include "MaterialEditor.h"
#include "Editor/EditorPaths.h"
#include "FloatParameters.h"
//#include "GraphNode.h"

#include <imgui.h>

void FireboxEditor::MaterialEditor::DrawMaterialEditor(bool& open, const Ref<Firebox::Material>& mat)
{
	if (open)
	{
		ImGui::Begin("Material Editor", &open);

		if (mat)
		{
			if (mat->GetDiffuse())
			{
				ImGui::Image((ImTextureRef)(uintptr_t)mat->GetDiffuse()->GetTextureID(), { 64.0f, 64.0f }, { 1, 0 }, { 0, 1 });
				ImGui::SameLine();
				ImGui::Text("Diffuse");
			}
			else
			{
				ImGui::ColorPicker4("Diffuse", &mat->GetDiffuseColor().r);
			}

			if (mat->GetRoughness())
			{
				ImGui::Image((ImTextureRef)(uintptr_t)mat->GetRoughness()->GetTextureID(), { 64.0f, 64.0f }, { 1, 0 }, { 0, 1 });
				ImGui::SameLine();
				ImGui::Text("Roughness");
			}
			else
			{
				EditorUI::FloatParameters::Float1(&mat->GetRoughnessValue(), "Roughness");
			}
		}
#if 0
		static GraphEditor::Options options;
		static GraphEditor::ViewState viewState;
		static GraphEditorDelegate delegate;
		static GraphEditor::FitOnScreen fit = GraphEditor::Fit_None;
		static bool showGraphEditor = true;

		if (ImGui::Button("Fit all nodes"))
		{
			fit = GraphEditor::Fit_AllNodes;
		}
		ImGui::SameLine();
		if (ImGui::Button("Fit selected nodes"))
		{
			fit = GraphEditor::Fit_SelectedNodes;
		}
		GraphEditor::Show(delegate, options, viewState, true, &fit);

#endif
		ImGui::End();
	}
}


