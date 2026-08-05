#pragma once

#include <filesystem>
#include <windows.h>

namespace FireboxEditor {

	class WindowsGameRunner
	{
	private:
		std::string m_RelativePath;
		std::string m_GamePath;

	public:
		WindowsGameRunner(const std::string& editorRelativePath, const std::string& gamePath);
		~WindowsGameRunner();

		void RunOnWindows();
	};
}