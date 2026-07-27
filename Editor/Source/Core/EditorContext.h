#pragma once

#include "Scene/Entity.h"
#include "Scene/Scene.h"

#include <functional>
#include <filesystem>

namespace FireboxEditor {

	namespace fs = std::filesystem;

	class EditorContext
	{
	public:
		EditorContext();
		
		Firebox::Entity GetSelectedEntity() const { return m_SelectedEntity; }
		void SetSelectedEntity(Firebox::Entity entity);
		void SetCurrentScene(Ref<Firebox::Scene>& scene);
		void SetSelectedDirectory(const fs::path& directory);
		void DeselectEntity();
		void DeselectDirectory(const fs::path& directory);
		void AddEntitySelectionListener(std::function<void(Firebox::Entity)> listener);
		void AddSceneChangeListener(std::function<void(const Ref<Firebox::Scene>&)> listener);
		void AddDirectorySelectionListener(std::function<void(const fs::path& directory)> listener);

		const Ref<Firebox::Scene>& GetCurrentScene() const { return m_CurrentScene; }
		const fs::path& GetSelectedDirectory() const { return m_SelectedDirectory; }

	private:
		Firebox::Entity m_SelectedEntity;
		Ref<Firebox::Scene> m_CurrentScene;
		fs::path m_SelectedDirectory;

		DynamicArray<std::function<void(Firebox::Entity)>> m_EntitySelectionListeners;
		DynamicArray<std::function<void(const Ref<Firebox::Scene>&)>> m_SceneChangeListeners;
		DynamicArray<std::function<void(const fs::path&)>> m_DirectorySelectionListeners;
	};
}