#include "EditorContext.h"

FireboxEditor::EditorContext::EditorContext() : m_CurrentScene(CreateRef<Firebox::Scene>())
{
}

void FireboxEditor::EditorContext::SetSelectedEntity(Firebox::Entity entity)
{
	m_SelectedEntity = entity;
	for (auto& listener : m_EntitySelectionListeners)
		listener(m_SelectedEntity);
}

void FireboxEditor::EditorContext::DeselectEntity()
{
	SetSelectedEntity({});
	for (auto& listener : m_EntitySelectionListeners)
		listener(m_SelectedEntity);
}

void FireboxEditor::EditorContext::AddEntitySelectionListener(std::function<void(Firebox::Entity)> listener)
{
	m_EntitySelectionListeners.push_back(listener);
}

void FireboxEditor::EditorContext::SetCurrentScene(Ref<Firebox::Scene>& scene)
{
	SetSelectedEntity({});
	m_CurrentScene = scene;
	for (auto& listener : m_SceneChangeListeners)
		listener(m_CurrentScene);
}

void FireboxEditor::EditorContext::AddSceneChangeListener(std::function<void(const Ref<Firebox::Scene>&)> listener)
{
	m_SceneChangeListeners.push_back(listener);
}

void FireboxEditor::EditorContext::SetSelectedDirectory(const fs::path& directory)
{
	m_SelectedDirectory = directory;
	for (auto& listener : m_DirectorySelectionListeners)
		listener(m_SelectedDirectory);
}

void FireboxEditor::EditorContext::DeselectDirectory(const fs::path& directory)
{
	SetSelectedDirectory({});
	for (auto& listener : m_DirectorySelectionListeners)
		listener(m_SelectedDirectory);
}

void FireboxEditor::EditorContext::AddDirectorySelectionListener(std::function<void(const fs::path& directory)> listener)
{
	m_DirectorySelectionListeners.push_back(listener);

}
