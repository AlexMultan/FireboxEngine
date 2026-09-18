#include "Entity.h"

Firebox::Entity::Entity()
{

}

Firebox::Entity::Entity(entt::entity handle) : m_Handle(handle), m_Scene(nullptr)
{
}

Firebox::Entity::Entity(entt::entity handle, Scene* scene) : m_Handle(handle), m_Scene(scene)
{
	
}