#pragma once

#include "Engine/Core/Core.h"
#include "Engine/Scene/Scene.h"
#include "Editor/Core/EditorContext.h"

namespace FireboxEditor {

	class HierarchyPanel
	{
	public:
		HierarchyPanel(const char* name, EditorContext& context);
		~HierarchyPanel();

		void RenderHierarchyrPanel(Ref<Firebox::Scene>& scene);

	private:
		String m_Name = "Hierachy";
		EditorContext& m_Context;
	};
}