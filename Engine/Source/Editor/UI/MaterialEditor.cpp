#include "MaterialEditor.h"

#include <imgui.h>

void FireboxEditor::MaterialEditor::DrawMaterialEditor(bool& open, const Ref<Firebox::Material>& mat)
{
	if (open)
	{
		ImGui::Begin("Material Editor", &open);

		if (mat)
		{
			ImGui::DragFloat("Shininess", 0, 0.1f);
			ImGui::DragFloat("Tiling", 0, 0.005f);
		}

		ImGui::End();
	}
}
