#pragma once

#include "Core/Core.h"
#include "imgui.h"
#include "Panels/IPanel.h"
#include "Core/EditorContext.h"

namespace FireboxEditor {

	class AssetBrowser
	{
	public:
		AssetBrowser(EditorContext& context);
		AssetBrowser(const char* name, EditorContext& context);
		~AssetBrowser();

		void RenderPanel();
		void DrawDirectoryNode(const char* name, const std::filesystem::path& directory);

	private:
		std::string m_Name = "Asset Browser";
		EditorContext& m_Context;
		std::filesystem::path m_EditorDirectory;
		std::filesystem::path m_EngineDirectory;
		std::filesystem::path m_CurrentDirectory;
	};
}