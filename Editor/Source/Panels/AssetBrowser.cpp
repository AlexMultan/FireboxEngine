#include "AssetBrowser.h"
#include "Core/Log.h"
#include "Core/EditorUtils.h"
#include "Editor/EditorPaths.h"

FireboxEditor::AssetBrowser::AssetBrowser() : m_CurrentDirectory(FireboxEditor::Paths::GetRootPath()),
    m_ParentDirectory(FireboxEditor::Paths::GetRootPath())
{

}

FireboxEditor::AssetBrowser::AssetBrowser(const char* name) : m_Name(name), m_CurrentDirectory(FireboxEditor::Paths::GetRootPath()), 
    m_ParentDirectory(FireboxEditor::Paths::GetRootPath())
{
    
}

FireboxEditor::AssetBrowser::~AssetBrowser()
{
    
}

void FireboxEditor::AssetBrowser::RenderPanel()
{
    ImGui::Begin(m_Name.c_str());

    if (m_CurrentDirectory != std::filesystem::path(m_ParentDirectory))
    {
        if (ImGui::Button("<-"))
        {
            m_CurrentDirectory = m_CurrentDirectory.parent_path();
        }
    }

    static float padding = 12.0f;
    static float thumbnailSize = 96.0f;
    float cellSize = thumbnailSize + padding;

    float panelWidth = ImGui::GetContentRegionAvail().x;
    int columnCount = (int)(panelWidth / cellSize);
    if (columnCount < 1)
        columnCount = 1;

    ImGui::Columns(columnCount, 0, false);

    for (auto& entry : std::filesystem::directory_iterator(m_CurrentDirectory))
    {
        const auto& path = entry.path();
        std::string filename = path.filename().string();

        uint icon = entry.is_directory() ? FireboxEditor::EditorUtils::GetDirectoryIcon() : FireboxEditor::EditorUtils::GetFileIcon();
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        ImGui::ImageButton(filename.c_str(), (ImTextureID)(uintptr_t)icon, { 96.0f, 96.0f }, { 1, 0 }, { 0, 1 });

        ImGui::PopStyleColor();
        if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
        {
            if (entry.is_directory())
                m_CurrentDirectory /= path.filename();
        }

        ImGui::TextWrapped(filename.c_str());

        ImGui::NextColumn();
    }
    ImGui::Columns(1);

    ImGui::End();
}


