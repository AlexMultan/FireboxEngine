#pragma once

#include "Core/EditorContext.h"

namespace FireboxEditor {

	class EditorSettings
	{
	public:
		EditorSettings();
		~EditorSettings();

		static void ShowWindow(EditorContext& context, bool* isOpen);

	private:
		static String s_WindowName;
	};
}