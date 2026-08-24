#include "EditorUtils.h"
#include "Rendering/Materials/Texture.h"
#include "Editor/EnginePaths.h"
#include "Editor/EditorPaths.h"
#include "Utils/String.h"

uint FireboxEditor::EditorUtils::s_MeshIcon = 0;
uint FireboxEditor::EditorUtils::s_DirectoryIcon = 0;
uint FireboxEditor::EditorUtils::s_FileIcon = 0;
uint FireboxEditor::EditorUtils::s_ReturnIcon = 0;
ImFont* FireboxEditor::EditorUtils::s_SelectedEntityNodeFont = nullptr;
ImFont* FireboxEditor::EditorUtils::s_TransformAxesFont = nullptr;
ImFont* FireboxEditor::EditorUtils::s_TransformValuesFont = nullptr;

void FireboxEditor::EditorUtils::Init(const ImGuiIO* io)
{
	s_MeshIcon = Firebox::Texture::Create(FireboxEditor::EditorContent::Get("Icons/T_MeshIcon.png").string())->GetTextureID();
	s_DirectoryIcon = Firebox::Texture::Create(FireboxEditor::EditorContent::Get("Icons/T_DirectoryIcon.png").string())->GetTextureID();
	s_FileIcon = Firebox::Texture::Create(FireboxEditor::EditorContent::Get("Icons/T_FileIcon.png").string())->GetTextureID();
	s_ReturnIcon = Firebox::Texture::Create(FireboxEditor::EditorContent::Get("Icons/T_ReturnIcon.png").string())->GetTextureID();
	s_SelectedEntityNodeFont = io->Fonts->AddFontFromFileTTF(FireboxEditor::EditorContent::Get("Fonts/Geist/static/Geist-Bold.ttf").string().c_str(), 17.0f);
	s_TransformAxesFont = io->Fonts->AddFontFromFileTTF(FireboxEditor::EditorContent::Get("Fonts/Geist_Mono/static/GeistMono-SemiBold.ttf").string().c_str(), 16.0f);
	s_TransformValuesFont = io->Fonts->AddFontFromFileTTF(FireboxEditor::EditorContent::Get("Fonts/Ubuntu_Sans/static/UbuntuSans_SemiCondensed-Medium.ttf").string().c_str(), 17.0f);
}

const uint FireboxEditor::EditorUtils::GetMeshIcon()
{
	return s_MeshIcon;
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
	return s_DirectoryIcon;
}

const uint FireboxEditor::EditorUtils::GetFileIcon()
{
	return s_FileIcon;
}

const uint FireboxEditor::EditorUtils::GetReturnIcon()
{
	return s_ReturnIcon;
}
