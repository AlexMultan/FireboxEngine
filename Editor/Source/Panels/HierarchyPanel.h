#pragma once

#include "Core/Core.h"
#include "Scene/Scene.h"
#include "Core/EditorContext.h"

namespace FireboxEditor {

	class HierarchyPanel
	{
	public:
		HierarchyPanel(const char* name, EditorContext& context);
		~HierarchyPanel();

		void RenderHierarchyrPanel(const Ref<Firebox::Scene>& scene);

	private:
		String m_Name = "Hierachy";
		EditorContext& m_Context;
		Firebox::Entity m_SelectedEntity;
	};
}