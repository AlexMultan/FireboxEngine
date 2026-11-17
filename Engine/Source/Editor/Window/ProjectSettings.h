#pragma once

#include "Core/EditorContext.h"

namespace FireboxEditor {

	class ProjectSettings
	{
	public:
		ProjectSettings();
		~ProjectSettings();

		static void ShowWindow(EditorContext& context, bool* isOpen);

	private:
		static String s_WindowName;
	};
}