#pragma once

#include "Engine/Core/Core.h"
#include <imgui.h>

namespace FireboxEditor {

	class EditorUtils
	{
	public:
		static void Init(const ImGuiIO* io);
		static const uint GetMeshIconTexture();
		static ImFont* GetSelectedEntityNodeFont();
		static ImFont* GetTransformAxesFont();

	private:
		static uint s_MeshIconTexture;
		static ImFont* s_SelectedEntityNodeFont;
		static ImFont* s_TransformAxesFont;
	};
}