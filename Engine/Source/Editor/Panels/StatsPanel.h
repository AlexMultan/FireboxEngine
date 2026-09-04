#pragma once

#include "Core/CoreMinimal.h"

#include <imgui.h>

namespace FireboxEditor {

	class StatsPanel
	{
	public:
		StatsPanel();
		StatsPanel(const char* name);
		~StatsPanel();

		void RenderPanel();

	private:
		String m_Name = "Stats";
	};
}