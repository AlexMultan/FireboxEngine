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

String FireboxEditor::EditorUtils::OpenFileDialog(const wchar_t* filterName, const wchar_t* filterPattern, const char* zenityPattern)
{
#ifdef _WIN32
    OPENFILENAMEW ofn;
    wchar_t szFile[260] = L"";

    std::wstring filter;
    filter += filterName;
    filter += L" (";
    filter += filterPattern;
    filter += L")";
    filter.push_back(L'\0');
    filter += filterPattern;
    filter.push_back(L'\0');
    filter += L"All Files (*.*)";
    filter.push_back(L'\0');
    filter += L"*.*";
    filter.push_back(L'\0');
    filter.push_back(L'\0');

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile) / sizeof(wchar_t);
    ofn.lpstrFilter = filter.c_str();
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (!GetOpenFileNameW(&ofn))
        return "";

    std::wstring selectedFile = ofn.lpstrFile;
    int len = WideCharToMultiByte(CP_UTF8, 0, selectedFile.c_str(), -1, nullptr, 0, nullptr, nullptr);
    String utf8Path(len, 0);
    WideCharToMultiByte(CP_UTF8, 0, selectedFile.c_str(), -1, utf8Path.data(), len, nullptr, nullptr);
    if (!utf8Path.empty() && utf8Path.back() == '\0')
        utf8Path.pop_back();

    return utf8Path;
#else
    std::string command = "zenity --file-selection --title=\"Select File\" --file-filter=\"";
    command += zenityPattern;
    command += "\" 2>/dev/null";

    std::array<char, 1024> buffer{};
    std::string result;

    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe)
        return "";

    while (fgets(buffer.data(), (int)buffer.size(), pipe.get()) != nullptr)
        result += buffer.data();

    while (!result.empty() && (result.back() == '\n' || result.back() == '\r'))
        result.pop_back();

    return result;
#endif
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
