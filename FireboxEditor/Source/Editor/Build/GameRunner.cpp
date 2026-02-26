#include "GameRunner.h"
#include "Editor/Build/Platform/WindowsGameRunner.h"
#include "Engine/Core/Log.h"

FireboxEditor::GameRunner::GameRunner(const std::string& editorRelativePath, const std::string& gamePath, const Extension& extension)
	: m_EditorRelativePath(editorRelativePath), m_GamePath(gamePath), m_Extension(extension)
{

}

FireboxEditor::GameRunner::~GameRunner()
{

}

void FireboxEditor::GameRunner::RunGame()
{
	switch (m_Extension)
	{
	case Extension::EXE:
		m_EditorRelativePath += ".exe";
		m_GamePath += ".exe";
		break;
	case Extension::SHELL:
		m_EditorRelativePath += ".sh";
		m_GamePath += ".sh";
		break;
	case Extension::RUN:
		m_EditorRelativePath += ".run";
		m_GamePath += ".run";
		break;
	}

#ifdef FIREBOX_PLATFORM_WIN64

	WindowsGameRunner windowsGameRunner(m_EditorRelativePath, m_GamePath);
	windowsGameRunner.RunOnWindows();
	STACK(windowsGameRunner);

#endif
}

void FireboxEditor::GameRunner::SetEditorRelativePath(const std::string& path)
{
	m_EditorRelativePath = path;
}

void FireboxEditor::GameRunner::SetGamePath(const std::string& path)
{
	m_GamePath = path;
}

void FireboxEditor::GameRunner::SetExtension(const Extension& extension)
{
	m_Extension = extension;
}
