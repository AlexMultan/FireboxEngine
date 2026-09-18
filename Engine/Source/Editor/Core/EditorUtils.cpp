#include "EditorUtils.h"
#include "Editor/EnginePaths.h"
#include "Editor/EditorPaths.h"
#include "Utils/String.h"

Ref<Firebox::Texture> FireboxEditor::EditorUtils::s_MeshIconTexture = nullptr;
Ref<Firebox::Texture> FireboxEditor::EditorUtils::s_DirectoryIconTexture = nullptr;
Ref<Firebox::Texture> FireboxEditor::EditorUtils::s_FileIconTexture = nullptr;
Ref<Firebox::Texture> FireboxEditor::EditorUtils::s_ReturnIconTexture = nullptr;
Ref<Firebox::Texture> FireboxEditor::EditorUtils::s_EmptySceneThumbnailTexture = nullptr;
Ref<Firebox::Texture> FireboxEditor::EditorUtils::s_BasicSceneThumbnailTexture = nullptr;
Ref<Firebox::Texture> FireboxEditor::EditorUtils::s_CameraSettingsIconTexture = nullptr;
Ref<Firebox::Texture> FireboxEditor::EditorUtils::s_RenderingSettingsIconTexture = nullptr;
Ref<Firebox::Texture> FireboxEditor::EditorUtils::s_PointLightIconTexture = nullptr;

ImFont* FireboxEditor::EditorUtils::s_SelectedEntityNodeFont = nullptr;
ImFont* FireboxEditor::EditorUtils::s_TransformAxesFont = nullptr;
ImFont* FireboxEditor::EditorUtils::s_TransformValuesFont = nullptr;
ImGuiIO* FireboxEditor::EditorUtils::s_ImGuiIO = nullptr;

void FireboxEditor::EditorUtils::Init(ImGuiIO* io)
{
	s_ImGuiIO = io;

	s_MeshIconTexture = Firebox::Texture::Create(FireboxEditor::EditorContent::Get("Icons/T_MeshIcon.png").string());
	s_DirectoryIconTexture = Firebox::Texture::Create(FireboxEditor::EditorContent::Get("Icons/T_DirectoryIcon.png").string());
	s_FileIconTexture = Firebox::Texture::Create(FireboxEditor::EditorContent::Get("Icons/T_FileIcon.png").string());
	s_ReturnIconTexture = Firebox::Texture::Create(FireboxEditor::EditorContent::Get("Icons/T_ReturnIcon.png").string());
	s_EmptySceneThumbnailTexture = Firebox::Texture::Create(FireboxEditor::EditorContent::Get("Icons/T_EmptySceneThumbnail.png").string());
	s_BasicSceneThumbnailTexture = Firebox::Texture::Create(FireboxEditor::EditorContent::Get("Icons/T_BasicSceneThumbnail.png").string());
	s_CameraSettingsIconTexture = Firebox::Texture::Create(FireboxEditor::EditorContent::Get("Icons/T_CameraIcon.png").string());
	s_RenderingSettingsIconTexture = Firebox::Texture::Create(FireboxEditor::EditorContent::Get("Icons/T_RenderingIcon.png").string());
	s_PointLightIconTexture = Firebox::Texture::Create(FireboxEditor::EditorContent::Get("Icons/T_PointLightIcon.png").string());

	s_SelectedEntityNodeFont = io->Fonts->AddFontFromFileTTF(FireboxEditor::EditorContent::Get("Fonts/Geist/static/Geist-Bold.ttf").string().c_str(), 17.0f);
	s_TransformAxesFont = io->Fonts->AddFontFromFileTTF(FireboxEditor::EditorContent::Get("Fonts/Geist_Mono/static/GeistMono-SemiBold.ttf").string().c_str(), 16.0f);
	s_TransformValuesFont = io->Fonts->AddFontFromFileTTF(FireboxEditor::EditorContent::Get("Fonts/Ubuntu_Sans/static/UbuntuSans_SemiCondensed-Medium.ttf").string().c_str(), 17.0f);
}

const uint FireboxEditor::EditorUtils::GetMeshIcon()
{
	return s_MeshIconTexture ? s_MeshIconTexture->GetTextureID() : 0;
}

const uint FireboxEditor::EditorUtils::GetCameraSettingsIcon()
{
	return s_CameraSettingsIconTexture ? s_CameraSettingsIconTexture->GetTextureID() : 0;
}

const uint FireboxEditor::EditorUtils::GetRenderingSettingsIcon()
{
	return s_RenderingSettingsIconTexture ? s_RenderingSettingsIconTexture->GetTextureID() : 0;
}

const uint FireboxEditor::EditorUtils::GetPointLightIcon()
{
	return s_PointLightIconTexture ? s_PointLightIconTexture->GetTextureID() : 0;
}

ImFont* FireboxEditor::EditorUtils::GetSelectedEntityNodeFont()
{
	return s_SelectedEntityNodeFont;
}

ImFont* FireboxEditor::EditorUtils::GetTransformAxesFont()
{
	return s_TransformAxesFont;
}

ImFont* FireboxEditor::EditorUtils::GetTransformValuesFont()
{
	return s_TransformValuesFont;
}

const uint FireboxEditor::EditorUtils::GetDirectoryIcon()
{
	return s_DirectoryIconTexture ? s_DirectoryIconTexture->GetTextureID() : 0;
}

const uint FireboxEditor::EditorUtils::GetFileIcon()
{
	return s_FileIconTexture ? s_FileIconTexture->GetTextureID() : 0;
}

const uint FireboxEditor::EditorUtils::GetReturnIcon()
{
	return s_ReturnIconTexture ? s_ReturnIconTexture->GetTextureID() : 0;
}

const uint FireboxEditor::EditorUtils::GetEmptySceneThumbnail()
{
	return s_EmptySceneThumbnailTexture ? s_EmptySceneThumbnailTexture->GetTextureID() : 0;
}

const uint FireboxEditor::EditorUtils::GetBasicSceneThumbnail()
{
	return s_BasicSceneThumbnailTexture ? s_BasicSceneThumbnailTexture->GetTextureID() : 0;
}

const ImVec2& FireboxEditor::EditorUtils::GetScreenSize()
{
	return s_ImGuiIO->DisplaySize;
}
