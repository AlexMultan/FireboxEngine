#pragma once

#include "Engine/Core/Core.h"
namespace FireboxEditor {

	class OutlinerPanel
	{
	public:
		OutlinerPanel();
		OutlinerPanel(const char* name);
		~OutlinerPanel();

		void RenderOutlinerPanel();

	private:
		String m_Name = "Outliner";
	};
}