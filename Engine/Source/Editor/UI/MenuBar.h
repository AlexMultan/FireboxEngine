#pragma once

#include "Scene/Scene.h"
#include "Core/EditorContext.h"

namespace FireboxEditor {

	class MenuBar
	{
	public:
		MenuBar(EditorContext& context);
		~MenuBar();

		void RenderMenuBar();

	private:
		EditorContext& m_Context;
		Ref<Firebox::Scene> m_Scene;
	};
}