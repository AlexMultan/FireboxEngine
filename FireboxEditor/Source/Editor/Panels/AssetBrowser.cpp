#include "AssetBrowser.h"
#include "Engine/Core/Log.h"

FireboxEditor::AssetBrowser::AssetBrowser(const char* name) : m_Name(name)
{
    
}

FireboxEditor::AssetBrowser::~AssetBrowser()
{
    
}

void FireboxEditor::AssetBrowser::RenderPanel()
{
    ImGui::Begin(m_Name.c_str());

    if (m_ShowFolderButton)
    {
        if (ImGui::Button("Folder", m_ButtonSize) && m_ShowFolderButton)
        {
            FIREBOX_EDITOR_INFO("Opened folder!");
            m_ShowFolderButton = false;
        }
    }

    if (!m_ShowFolderButton)
    {
        if (ImGui::Button("Mesh", m_ButtonSize))
        {
            FIREBOX_EDITOR_INFO("Opened first person arms model");
        }
    }

    ImGui::End();
}


