#pragma once

#include "Engine/Core/Core.h"
#include "Engine/Layers/Layer.h"
#include "imgui.h"
#include "SDL3/SDL.h"
#include "Editor/Panels/AssetBrowser.h"
#include "Editor/Panels/PropertiesPanel.h"

namespace FireboxEditor {

	class EditorViewport : public Firebox::Layer
	{
	private:
		ImGuiIO* io;
		bool showFolderButton = true;

		AssetBrowser* m_AssetBrowser;
		PropertiesPanel* m_PropertiesPanel;

	public:
		EditorViewport();
		~EditorViewport();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEditorUIRender() override;
		virtual void OnEvent(SDL_Event& event) override;

	};
}