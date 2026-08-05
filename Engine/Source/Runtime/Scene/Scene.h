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

		Entity CreateEntity();
		Entity CreateEntity(const String& name);
		void DestroyEntity(Entity entity);
		void OnUpdate(float deltaTime);
		void SaveScene(const String& filename);
		static Ref<Scene> LoadScene(const String& filename);
		inline const entt::registry& GetRegistry() const { return m_Registry; }
		inline const String& GetSceneName() const { return m_SceneName; }
		inline void SetSceneName(const String& name) { m_SceneName = name; }

	private:
		entt::registry m_Registry;
		friend class Entity;
		String m_DefaultEntityTag = "NewEntity";
		String m_SceneName = "NewScene";
	};
}