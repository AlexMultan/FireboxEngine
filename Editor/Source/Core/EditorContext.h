#pragma once

#include "Scene/Entity.h"
#include "Scene/Scene.h"

#include <functional>

namespace FireboxEditor {

	class EditorContext
	{
	public:
		Firebox::Entity selectedEntity;
		Ref<Firebox::Scene> currentScene;

		std::function<void(Firebox::Entity)> OnSelectionChanged;
		std::function<void(Ref<Firebox::Scene>&)> OnSceneChanged;

		inline void SetSelected(Firebox::Entity entity)
		{
			selectedEntity = entity;
			if (OnSelectionChanged)
				OnSelectionChanged(entity);
		}

		inline void ClearSelection()
		{
			selectedEntity = {};
			if (OnSelectionChanged)
				OnSelectionChanged(selectedEntity);
		}

		inline void SetCurrentScene(Ref<Firebox::Scene>& scene)
		{
			ClearSelection();
			currentScene = scene;
			if (OnSceneChanged)
				OnSceneChanged(currentScene);
		}
	};
}