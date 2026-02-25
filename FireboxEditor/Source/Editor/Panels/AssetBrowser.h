#pragma once

#include "Engine/Core/Core.h"
#include "imgui.h"
#include "Editor/Panels/IPanel.h"
#include <string>

namespace FireboxEditor {

	class AssetBrowser : public IPanel
	{
	private:
		std::string m_Name = "Asset Browser";
		ImVec2 m_ButtonSize = ImVec2(70.0f, 70.0f);
		bool m_ShowFolderButton = true;

	public:
		AssetBrowser(const char* name);
		~AssetBrowser();

		virtual void RenderPanel() override;
	};
}