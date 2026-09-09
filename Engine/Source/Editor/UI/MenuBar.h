#pragma once

#include "Scene/Scene.h"
#include "Core/EditorContext.h"

#include <SDL3/SDL_dialog.h>

namespace FireboxEditor {

	class MenuBar
	{
	public:
		MenuBar(EditorContext& context);
		~MenuBar();

		void RenderMenuBar();

	private:
		void AddStaticMeshEntity(const String& name, const String& path);

	private:
		EditorContext& m_Context;
		Ref<Firebox::Scene> m_Scene;
	};
}