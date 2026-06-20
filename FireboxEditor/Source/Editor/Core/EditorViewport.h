#pragma once

#include "Engine/Layers/Layer.h"
#include "Editor/Panels/AssetBrowser.h"
#include "Editor/Panels/PropertiesPanel.h"
#include "Editor/UI/MenuBar.h"
#include "Editor/Panels/ConsolePanel.h"
#include "Editor/Panels/ViewportPanel.h"
#include "Editor/Panels/OutlinerPanel.h"
#include "Engine/Rendering/Resources/Framebuffer.h"
#include "Engine/Rendering/Camera/PerspectiveCamera.h"
#include "Engine/Components/Components.h"
#include "Engine/Components/LightComponents.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Scene/Entity.h"

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
		OutlinerPanel m_OutlinerPanel;

		Ref<Firebox::Scene> m_CurrentScene;

		Ref<Firebox::PerspectiveCamera> m_EditorCamera;
		Ref<Firebox::Framebuffer> m_Framebuffer;
		Ref<Firebox::Mesh> m_CubeMesh;
		Ref<Firebox::Material> m_CubeMaterial;
		Ref<Firebox::Material> m_SecondCubeMaterial;
		TransformComponent m_CubeTransform;
		String m_CubeTag;
		String m_SecondCubeTag;
		TransformComponent m_SecondCubeTransform;
		Firebox::DirectionalLightComponent m_DirectionalLight;
		Firebox::Entity m_CubeEntity{};
		Firebox::Entity m_BunnyEntity{};
		Ref<Firebox::StaticMesh> m_BunnyModel;
		Ref<Firebox::Material> m_BunnyMat;
	};
}