#pragma once

#include "Engine/Core/Core.h"
#include "Engine/Layers/Layer.h"
#include "Editor/Panels/AssetBrowser.h"
#include "Editor/Panels/PropertiesPanel.h"
#include "Editor/UI/MenuBar.h"
#include "Editor/Panels/Debugger.h"

#include "imgui.h"
#include "SDL3/SDL.h"

namespace FireboxEditor {

	class EditorViewport : public Firebox::Layer
	{
	private:
		ImGuiIO* io;
		bool showFolderButton = true;
		ImGuiWindowFlags m_WindowFlags;
		ImGuiDockNodeFlags m_DockNodeFlags;

		FireboxEditor::AssetBrowser m_AssetBrowser;
		FireboxEditor::PropertiesPanel m_PropertiesPanel;
		FireboxEditor::MenuBar m_MenuBar;
		FireboxEditor::Debugger m_DebuggerPanel;

	public:
		EditorViewport();
		~EditorViewport();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEditorUIRender() override;
		virtual void OnEvent(SDL_Event& event) override;

	};
}