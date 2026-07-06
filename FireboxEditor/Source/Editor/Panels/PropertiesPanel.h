#pragma once

#include "Engine/Core/Core.h"
#include "Editor/Core/EditorContext.h"

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

		inline void SetTransformPropertiesFont(ImFont* font) { m_TransformPropertiesFont = font; }

	private:
		String m_Name = "Details";
		float m_DragStrength = 0.2f;
		ImFont* m_TransformPropertiesFont = nullptr;
		EditorContext& m_Context;
	};
}