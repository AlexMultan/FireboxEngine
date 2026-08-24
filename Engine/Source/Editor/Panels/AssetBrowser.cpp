#include "AssetBrowser.h"
#include "Core/Log.h"
#include "Core/EditorUtils.h"
#include "Editor/EditorPaths.h"
#include "Editor/EnginePaths.h"

FireboxEditor::AssetBrowser::AssetBrowser(EditorContext& context) : m_CurrentDirectory(FireboxEditor::EditorContent::GetRootPath()), 
    m_EditorDirectory(FireboxEditor::EditorContent::GetRootPath()), m_EngineDirectory(Firebox::EngineContent::GetRootPath()), m_Context(context)
{
    m_Context.AddDirectorySelectionListener([this](const fs::path& directory)
        {
            m_CurrentDirectory = directory;
        });
}

FireboxEditor::AssetBrowser::AssetBrowser(const char* name, EditorContext& context) : m_Name(name), 
    m_CurrentDirectory(FireboxEditor::EditorContent::GetRootPath()), m_EditorDirectory(FireboxEditor::EditorContent::GetRootPath()), 
    m_EngineDirectory(Firebox::EngineContent::GetRootPath()), m_Context(context)
{
    m_Context.AddDirectorySelectionListener([this](const fs::path& directory)
        {
            m_CurrentDirectory = directory;
        });
}

FireboxEditor::AssetBrowser::~AssetBrowser()
{
    
}

void FireboxEditor::AssetBrowser::RenderPanel()
{
    ImGui::Begin(m_Name.c_str());

    static float leftWidth = 250.0f;
    float paneHeight = ImGui::GetContentRegionAvail().y;

    ImGui::BeginChild("LeftPane", ImVec2(leftWidth, paneHeight), true);
    
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 6.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 2.0f));

    DrawDirectoryNode("Editor Content", m_EditorDirectory);
    DrawDirectoryNode("Engine Content", m_EngineDirectory);

    ImGui::PopStyleVar(3);

    ImGui::EndChild();

    ImGui::SameLine();

    ImGui::Button("##01", ImVec2(6.0f, paneHeight));
    if (ImGui::IsItemActive())
    {
        leftWidth += ImGui::GetIO().MouseDelta.x;
    }

    ImGui::SameLine();

    ImGui::BeginChild("RightPane", ImVec2(0, paneHeight), true);

    static float padding = 12.0f;
    static float thumbnailSize = 96.0f;
    float cellSize = thumbnailSize + padding;

    float panelWidth = ImGui::GetContentRegionAvail().x;
    int columnCount = (int)(panelWidth / cellSize);

    if (columnCount < 1)
        columnCount = 1;

    String hintDirectory = "Search in " + m_CurrentDirectory.filename().string();
    static char textBuffer[128] = "";
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, {15.0f, 2.0f});
    if (ImGui::InputTextWithHint("##AssetSearch", hintDirectory.c_str(), textBuffer, IM_ARRAYSIZE(textBuffer)))
    {

    }
    ImGui::PopStyleVar(2);
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

    ImGui::EndChild();

    ImGui::End();
}

void FireboxEditor::AssetBrowser::DrawDirectoryNode(const char* name, const std::filesystem::path& directory)
{
    ImGui::SetCursorPosX(0.0f);
    float paddingX = 10.0f;

    bool hasSubDirs = false;
    for (const auto& entry : std::filesystem::directory_iterator(directory))
    {
        if (entry.is_directory())
        {
            hasSubDirs = true;
        }
    }

    ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_OpenOnArrow;
    if (!hasSubDirs)
        nodeFlags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
    if (m_CurrentDirectory == directory)
    {
        ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.29f, 0.47f, 0.85f, 1.00f));
        ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.31f, 0.53f, 0.98f, 1.00f));
    }

    ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.29f, 0.47f, 0.85f, 1.00f));
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(paddingX, 3.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);

    bool open = ImGui::TreeNodeEx(directory.string().c_str(), nodeFlags, "%s", name);

    if(m_CurrentDirectory != directory)
        ImGui::PopStyleColor();
    else
        ImGui::PopStyleColor(3);

    ImGui::PopStyleVar(2);

    if(ImGui::IsItemClicked(ImGuiMouseButton_Left))
        m_CurrentDirectory = directory;

    if (open && hasSubDirs)
    {
        for (auto& entry : std::filesystem::directory_iterator(directory))
        {
            if (entry.is_directory())
            {
                String filename = entry.path().filename().string();
                DrawDirectoryNode(filename.c_str(), entry.path());
            }
        }
    }

    if (open && !(nodeFlags & ImGuiTreeNodeFlags_NoTreePushOnOpen))
        ImGui::TreePop();
}


