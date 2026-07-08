#pragma once

#include "Engine/Components/Components.h"

namespace FireboxEditor {

	class MaterialEditor
	{
	public:
		static void DrawMaterialEditor(bool& open, const Ref<Firebox::Material>& mat);
	};
}