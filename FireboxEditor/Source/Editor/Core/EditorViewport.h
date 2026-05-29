#pragma once

#include "Engine/Layers/Layer.h"
#include "Editor/Panels/AssetBrowser.h"
#include "Editor/Panels/PropertiesPanel.h"
#include "Editor/UI/MenuBar.h"
#include "Editor/Panels/Debugger.h"
#include "Editor/Panels/ConsolePanel.h"
#include "Editor/Panels/ViewportPanel.h"

#include "imgui.h"

namespace FireboxEditor {

	class EditorViewport : public Firebox::Layer
	{
	private:
		ImGuiIO* io;
		bool showFolderButton = true;
		ImGuiWindowFlags m_WindowFlags;
		ImGuiDockNodeFlags m_DockNodeFlags;

		AssetBrowser m_AssetBrowser;
		PropertiesPanel m_PropertiesPanel;
		MenuBar m_MenuBar;
		Debugger m_DebuggerPanel;
		ConsolePanel m_ConsolePanel;
		ViewportPanel m_ViewportPanel;

		uint m_FBO;
		uint m_ViewportTextureBuffer;

		/*float m_CameraSpeed = 0.05f;*/

	public:
		EditorViewport();
		~EditorViewport();

		void OnGenFrameBuffer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(float deltaTime) override;
		virtual void OnEditorUIRender() override;
		virtual void OnSecondWindowRender() override;
		virtual void OnEvent(Firebox::Event& event) override;

	};
}