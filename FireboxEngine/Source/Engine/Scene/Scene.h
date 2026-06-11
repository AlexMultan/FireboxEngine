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
		void GetAllEntities();

	private:
		entt::registry m_Registry;
		friend class Entity;
	};
}