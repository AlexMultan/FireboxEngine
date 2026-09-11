#pragma once

#include "Scene/Scene.h"
#include "Core/EditorContext.h"

#ifdef _WIN32
    #include <windows.h>
    #include <commdlg.h>
#else
    #include <array>
    #include <cstdio>
    #include <memory>
#endif


namespace FireboxEditor {

	class MenuBar
	{
	public:
		MenuBar(EditorContext& context);
		~MenuBar();

		void RenderMenuBar();

	private:
		void AddStaticMeshEntity(const String& name, const String& path);
		String OpenFileDialog(const wchar_t* filterName, const wchar_t* filterPattern, const char* zenityPattern);

	private:
		EditorContext& m_Context;
		Ref<Firebox::Scene> m_Scene;
	};
}