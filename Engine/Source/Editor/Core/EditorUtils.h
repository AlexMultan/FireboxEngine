#pragma once

#include "Core/Core.h"
#include <imgui.h>

namespace FireboxEditor {

	class EditorUtils
	{
	public:
		static void Init(const ImGuiIO* io);
		static const uint GetMeshIcon();
		static ImFont* GetSelectedEntityNodeFont();
		static ImFont* GetTransformAxesFont();
		static ImFont* GetTransformValuesFont();
		static const uint GetDirectoryIcon();
		static const uint GetFileIcon();
		static const uint GetReturnIcon();

	private:
		static uint s_MeshIcon;
		static ImFont* s_SelectedEntityNodeFont;
		static ImFont* s_TransformAxesFont;
		static ImFont* s_TransformValuesFont;
		static uint s_DirectoryIcon;
		static uint s_FileIcon;
		static uint s_ReturnIcon;
	};
}