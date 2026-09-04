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
#include "Scene/Entity.h"
#include "EditorContext.h"
#include "Components/CoreComponents.h"
#include "Components/LightComponents.h"
#include "Components/RenderComponents.h"
#include "Components/AnimationComponents.h"

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
		EditorContext m_EditorContext;
		ImGuiWindowFlags m_WindowFlags;
		ImGuiDockNodeFlags m_DockNodeFlags;
		String m_EditorIni;

		AssetBrowser m_AssetBrowser;
		PropertiesPanel m_PropertiesPanel;
		MenuBar m_MenuBar;
		ConsolePanel m_ConsolePanel;
		ViewportPanel m_ViewportPanel;
		HierarchyPanel m_HierarchyPanel;
		StatsPanel m_StatsPanel;

		Ref<Firebox::PerspectiveCamera> m_EditorCamera;
		Firebox::Entity m_BunnyEntity{};
		Ref<Firebox::StaticMesh> m_BunnyModel;

		Firebox::Entity m_JerrycanEntity{};
		Ref<Firebox::Material> m_JerrycanMaterial;
		Ref<Firebox::StaticMesh> m_JerrycanMesh;

		Firebox::Entity m_GunEntity{};
		Ref<Firebox::Material> m_GunMaterial;
		Ref<Firebox::StaticMesh> m_GunMesh;

		Firebox::Entity m_RifleEntity{};
		Ref<Firebox::Material> m_RifleMaterial;
		Ref<Firebox::Material> m_RifleMaterialMag;
		Ref<Firebox::StaticMesh> m_RifleMesh;
	};
}