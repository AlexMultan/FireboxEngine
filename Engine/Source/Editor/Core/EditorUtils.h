#pragma once

#include "Core/CoreMinimal.h"
#include "Rendering/Materials/Texture.h"

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
		static const uint GetCameraSettingsIcon();
		static const uint GetRenderingSettingsIcon();
		static const uint GetPointLightIcon();

	private:
		static Ref<Firebox::Texture> s_MeshIconTexture;
		static Ref<Firebox::Texture> s_DirectoryIconTexture;
		static Ref<Firebox::Texture> s_FileIconTexture;
		static Ref<Firebox::Texture> s_ReturnIconTexture;
		static Ref<Firebox::Texture> s_EmptySceneThumbnailTexture;
		static Ref<Firebox::Texture> s_BasicSceneThumbnailTexture;
		static Ref<Firebox::Texture> s_CameraSettingsIconTexture;
		static Ref<Firebox::Texture> s_RenderingSettingsIconTexture;
		static Ref<Firebox::Texture> s_PointLightIconTexture;

		static ImGuiIO* s_ImGuiIO;
		static ImFont* s_SelectedEntityNodeFont;
		static ImFont* s_TransformAxesFont;
		static ImFont* s_TransformValuesFont;
	};
}