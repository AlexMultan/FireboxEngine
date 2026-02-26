#pragma once

#include "Engine/Core/Core.h"

#include <string>

namespace FireboxEditor {

	enum class Extension
	{
		EXE = 0,
		SHELL,
		RUN
	};

	class GameRunner
	{
	private:
		std::string m_EditorRelativePath = "FireboxEditor/FireboxEditor";
		std::string m_GamePath = "Game/Game";
		Extension m_Extension = Extension::EXE;

	public:
		GameRunner(const std::string& editorRelativePath, const std::string& gamePath, const Extension& extension);
		virtual ~GameRunner();

		void RunGame();

		void SetEditorRelativePath(const std::string& path);
		void SetGamePath(const std::string& path);
		void SetExtension(const Extension& extension);

		inline const std::string& GetRelativePath() const
		{
			return m_EditorRelativePath;
		}

		inline const std::string& GetGamePath() const
		{
			return m_EditorRelativePath;
		}

		inline const Extension& GetExtension() const
		{
			return m_Extension;
		}
	};
}