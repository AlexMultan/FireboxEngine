#pragma once

#include "Engine/Scene/Entity.h"

#include <functional>

namespace FireboxEditor {

	class EditorContext
	{
	public:
		Firebox::Entity selectedEntity;

		std::function<void(Firebox::Entity)> OnSelectionChanged;

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
	};
}