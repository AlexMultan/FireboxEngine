#pragma once

#include "Core/Core.h"

#include <entt.hpp>

namespace Firebox {

	class Entity;

	class FIREBOX_API Scene
	{
	public:
		Scene();
		~Scene();
		Scene(const Scene&) = delete;
		Scene& operator=(const Scene&) = delete;
		Scene(Scene&&) = default;
		Scene& operator=(Scene&&) = default;

		Entity CreateEntity(const String& name);
		void OnUpdate(float deltaTime);
		void SaveScene(const String& filename);
		static Scene LoadScene(const String& filename);
		inline const DynamicArray<Entity>& GetAllEntities() const { return m_SceneEntities; }
		inline const String& GetSceneName() const { return m_SceneName; }
		inline void SetSceneName(const String& name) { m_SceneName = name; }
		inline void SetEntities(const DynamicArray<Entity>& entities) { m_SceneEntities = entities; }

	private:
		entt::registry m_Registry;
		DynamicArray<Entity> m_SceneEntities;
		friend class Entity;
		String m_DefaultEntityTag = "NewEntity";
		String m_SceneName = "NewScene";
	};
}