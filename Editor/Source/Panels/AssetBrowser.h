#pragma once

#include "Core/Core.h"
#include "imgui.h"
#include "Panels/IPanel.h"

#include <filesystem>

namespace FireboxEditor {

	class AssetBrowser : public IPanel
	{
	public:
		AssetBrowser();
		AssetBrowser(const char* name);
		~AssetBrowser();

		virtual void RenderPanel() override;

	private:
		std::string m_Name = "Asset Browser";
		std::filesystem::path m_ParentDirectory;
		std::filesystem::path m_CurrentDirectory;
	};
}