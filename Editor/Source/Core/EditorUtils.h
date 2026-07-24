#pragma once

#include "Core/Core.h"
#include <imgui.h>

namespace FireboxEditor {

	class EditorUtils
	{
	public:
		static void Init(const ImGuiIO* io);
		static const uint GetMeshIconTexture();
		static ImFont* GetSelectedEntityNodeFont();
		static ImFont* GetTransformAxesFont();
		static const uint GetDirectoryIcon();
		static const uint GetFileIcon();

	private:
		static uint s_MeshIconTexture;
		static ImFont* s_SelectedEntityNodeFont;
		static ImFont* s_TransformAxesFont;
		static uint s_DirectoryIcon;
		static uint s_FileIcon;
	};
}