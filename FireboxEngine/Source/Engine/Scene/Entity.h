#pragma once

#include "Scene.h"
#include "Engine/Utils/Assert.h"
#include "Engine/Core/UUID.h"

#include <utility>

namespace Firebox {

	class FIREBOX_API Entity
	{
	public:
		Entity();
		Entity(entt::entity handle, Scene* scene);

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.any_of<T>(m_Handle);
		}

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			return m_Scene->m_Registry.emplace_or_replace<T>(m_Handle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			ASSERT(HasComponent<T>(), "Entity doesn't have a component");
			return m_Scene->m_Registry.get<T>(m_Handle);
		}

		template<typename T>
		T& RemoveComponent()
		{
			ASSERT(!HasComponent<T>(), "Entity doesn't have a component");
			return m_Scene->m_Registry.remove<T>(m_Handle);
		}

		inline const uint64& GetID() const { return m_UUID; }

	private:
		entt::entity m_Handle;
		Scene* m_Scene = nullptr;
		UUID m_UUID{};
	};
}