#pragma once

#include "Engine/Core/Core.h"
#include "Engine/Scene/Scene.h"
#include "Editor/Core/EditorContext.h"

namespace FireboxEditor {

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel(const char* name, EditorContext& context);
		~SceneHierarchyPanel();

		void RenderSceneHierarchyrPanel(Ref<Firebox::Scene>& scene);

	private:
		String m_Name = "Outliner";
		EditorContext& m_Context;
	};
}