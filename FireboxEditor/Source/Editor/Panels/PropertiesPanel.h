#pragma once

#include "Engine/Core/Core.h"
#include "Engine/Components/Components.h"

#include <imgui.h>

namespace FireboxEditor {

	class PropertiesPanel
	{
	public:
		PropertiesPanel();
		PropertiesPanel(const char* name);
		~PropertiesPanel();

		void RenderPanel(TransformComponent& transformComp);

		void SetDragStrangth(const float& strength);
		void PushTreeNodeStyle();
		void PopTreeNodeStyle();

		inline void SetTransformPropertiesFont(ImFont* font)
		{
			m_TransformPropertiesFont = font;
		}

	private:
		String m_Name = "Properties";
		float m_DragStrength = 0.2f;
		ImFont* m_TransformPropertiesFont = nullptr;
	};
}