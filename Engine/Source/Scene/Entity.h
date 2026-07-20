#pragma once

#include "Scene.h"
#include "Utils/Assert.h"

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
			return m_Scene->m_Registry.emplace_or_replace<T>(m_Handle, std::forward<Args>(args)... );
		}

		template<typename T>
		T& GetComponent()
		{
			FB_ASSERT(HasComponent<T>(), "Entity doesn't have a component");
			return m_Scene->m_Registry.get<T>(m_Handle);
		}

		template<typename T>
		T& RemoveComponent()
		{
			FB_ASSERT(!HasComponent<T>(), "Entity doesn't have a component");
			return m_Scene->m_Registry.remove<T>(m_Handle);
		}

		operator bool() const
		{
			return m_Scene != nullptr && m_Handle != entt::null && m_Scene->m_Registry.valid(m_Handle);
		}

	private:
		entt::entity m_Handle{ entt::null };
		Scene* m_Scene = nullptr;
	};
}