#pragma once

#include "Core/Core.h"

#include <entt.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace Firebox {

	class Entity;

	class FIREBOX_API Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const String& name);
		void OnUpdate(float deltaTime);
		void SaveScene(const json& j, const String& filename);
		json LoadScene(const String& filename);
		inline DynamicArray<Entity>& GetAllEntities() { return m_SceneEntities; }

	private:
		entt::registry m_Registry;
		DynamicArray<Entity> m_SceneEntities;
		friend class Entity;
		String m_DefaultEntityTag = "NewEntity";
	};
}