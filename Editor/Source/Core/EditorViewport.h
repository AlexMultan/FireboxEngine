#pragma once

#include "Layers/Layer.h"
#include "Panels/AssetBrowser.h"
#include "Panels/PropertiesPanel.h"
#include "UI/MenuBar.h"
#include "Panels/ConsolePanel.h"
#include "Panels/ViewportPanel.h"
#include "Panels/HierarchyPanel.h"
#include "Panels/StatsPanel.h"
#include "Rendering/Camera/PerspectiveCamera.h"
#include "Components/Components.h"
#include "Components/LightComponents.h"
#include "Scene/Scene.h"
#include "Scene/Entity.h"
#include "EditorContext.h"

#include "imgui.h"

namespace FireboxEditor {

	class EditorViewport : public Firebox::Layer
	{
	public:
		EditorViewport();
		~EditorViewport();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(float deltaTime) override;
		virtual void OnRender(float deltaTime) override;
		virtual void OnEditorUIRender() override;
		virtual void OnEvent(Firebox::Event& event) override;

 
	private:
		ImGuiIO* io;
		bool showFolderButton = true;
		ImGuiWindowFlags m_WindowFlags;
		ImGuiDockNodeFlags m_DockNodeFlags;
		ImFont* m_TransformPropertiesFont = nullptr;

		AssetBrowser m_AssetBrowser;
		PropertiesPanel m_PropertiesPanel;
		MenuBar m_MenuBar;
		ConsolePanel m_ConsolePanel;
		ViewportPanel m_ViewportPanel;
		HierarchyPanel m_HierarchyPanel;
		StatsPanel m_StatsPanel;
		EditorContext m_EditorContext;

		Ref<Firebox::Scene> m_CurrentScene;

		Ref<Firebox::PerspectiveCamera> m_EditorCamera;
		Ref<Firebox::StaticMesh> m_CubeMesh;
		Ref<Firebox::Material> m_SecondCubeMaterial;
		TransformComponent m_CubeTransform;
		String m_CubeTag;
		String m_SecondCubeTag;
		TransformComponent m_SecondCubeTransform;
		Firebox::Entity m_DirectionalLight;
		Firebox::Entity m_CubeEntity{};
		Firebox::Entity m_FloorEntity{};
		Firebox::Entity m_BunnyEntity{};
		Ref<Firebox::StaticMesh> m_BunnyModel;

		Firebox::Entity m_JerrycanEntity{};
		Ref<Firebox::Material> m_JerrycanMaterial;
		Ref<Firebox::StaticMesh> m_JerrycanMesh;
	};
}