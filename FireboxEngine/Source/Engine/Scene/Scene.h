#pragma once

#include "Engine/Core/Core.h"

#include <entt.hpp>

namespace Firebox {

	class Entity;

	class FIREBOX_API Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const String& name);
		void OnUpdate(float deltaTime);
		inline DynamicArray<Entity>& GetAllEntities() { return m_SceneEntities; }

	private:
		entt::registry m_Registry;
		DynamicArray<Entity> m_SceneEntities;
		friend class Entity;
		String m_DefaultEntityTag = "NewEntity";
	};
}