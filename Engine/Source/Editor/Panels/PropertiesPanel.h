#pragma once

#include "Core/Core.h"
#include "Core/EditorContext.h"

#include <imgui.h>

namespace FireboxEditor {

	class PropertiesPanel
	{
	public:
		PropertiesPanel(const char* name, EditorContext& context);
		~PropertiesPanel();

		void RenderPanel();

		void SetDragStrangth(const float& strength);
		void PushTreeNodeStyle();
		void PopTreeNodeStyle();

	private:
		String m_Name = "Details";
		float m_DragStrength = 0.2f;
		EditorContext& m_Context;
		Firebox::Entity m_SelectedEntity;
	};
}