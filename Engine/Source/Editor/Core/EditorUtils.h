#pragma once

#include "Core/CoreMinimal.h"
#include <imgui.h>

namespace FireboxEditor {

	class EditorUtils
	{
	public:
		static void Init(ImGuiIO* io);
		static const uint GetMeshIcon();
		static ImFont* GetSelectedEntityNodeFont();
		static ImFont* GetTransformAxesFont();
		static ImFont* GetTransformValuesFont();
		static const uint GetDirectoryIcon();
		static const uint GetFileIcon();
		static const uint GetReturnIcon();
		static const uint GetEmptySceneThumbnail();
		static const uint GetBasicSceneThumbnail();
		static const ImVec2& GetScreenSize();

	private:
		static ImGuiIO* s_ImGuiIO;
		static uint s_MeshIcon;
		static ImFont* s_SelectedEntityNodeFont;
		static ImFont* s_TransformAxesFont;
		static ImFont* s_TransformValuesFont;
		static uint s_DirectoryIcon;
		static uint s_FileIcon;
		static uint s_ReturnIcon;
		static uint s_EmptySceneThumbnail;
		static uint s_BasicSceneThumbnail;
	};
}