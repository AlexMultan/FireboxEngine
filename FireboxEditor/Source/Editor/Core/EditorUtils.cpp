#include "EditorUtils.h"
#include "Engine/Rendering/Resources/Texture.h"
#include "Engine/Core/EngineAssets.h"
#include "Engine/Core/EditorPaths.h"
#include "Engine/Utils/String.h"

uint FireboxEditor::EditorUtils::s_MeshIconTexture = 0;
ImFont* FireboxEditor::EditorUtils::s_SelectedEntityNodeFont = nullptr;
ImFont* FireboxEditor::EditorUtils::s_TransformAxesFont = nullptr;

void FireboxEditor::EditorUtils::Init(const ImGuiIO* io)
{
	s_MeshIconTexture = Firebox::Texture::Create(Firebox::EngineAssets::Get("Icons/T_MeshIcon.png").string())->GetTextureID();
	s_SelectedEntityNodeFont = io->Fonts->AddFontFromFileTTF(FireboxEditor::Paths::Resource("Fonts/JetBrainsMono/JetBrainsMono-ExtraBold.ttf").string().c_str(), 18.0f);
	s_TransformAxesFont = io->Fonts->AddFontFromFileTTF(FireboxEditor::Paths::Resource("Fonts/Geist_Mono/static/GeistMono-SemiBold.ttf").string().c_str(), 16.0f);
}

const uint FireboxEditor::EditorUtils::GetMeshIconTexture()
{
	return s_MeshIconTexture;
}

ImFont* FireboxEditor::EditorUtils::GetSelectedEntityNodeFont()
{
	return s_SelectedEntityNodeFont;
}

ImFont* FireboxEditor::EditorUtils::GetTransformAxesFont()
{
	return s_TransformAxesFont;
}
