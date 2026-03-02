#include "WindowsGameRunner.h"
#include "Engine/Core/Log.h"
#include "Engine/Utils/Assert.h"

FireboxEditor::WindowsGameRunner::WindowsGameRunner(const std::string& editorRelativePath, const std::string& gamePath)
    :m_RelativePath(editorRelativePath), m_GamePath(gamePath)
{

}

FireboxEditor::WindowsGameRunner::~WindowsGameRunner()
{

}

void FireboxEditor::WindowsGameRunner::RunOnWindows()
{
    wchar_t path[MAX_PATH];
    GetModuleFileNameW(NULL, path, MAX_PATH);
    std::string file = std::filesystem::path(path).generic_string();

    size_t pos = 0;
    while ((pos = file.find(m_RelativePath, pos)) != std::string::npos)
    {
        file.replace(pos, m_RelativePath.length(), m_GamePath);
        pos += m_GamePath.length();
    }
    ASSERT_EDITOR(std::filesystem::exists(std::filesystem::path(file)), "Game executable not found!");
    FIREBOX_EDITOR_INFO("[WINDOWS] Opened: {0}", file);
    std::system(file.c_str());
}