#pragma once

#include "Scene/Scene.h"

namespace FireboxEditor {

	class MenuBar
	{
	public:
		MenuBar();
		~MenuBar();

		void RenderMenuBar(Ref<Firebox::Scene>& scene);
	};
}