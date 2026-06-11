#include "Scene.h"
#include "Engine/Components/Components.h"
#include "Engine/Rendering/Renderer3D.h"
#include "Entity.h"

namespace Firebox {

	Scene::Scene()
	{
		
	}

	Scene::~Scene()
	{

	}


	Entity Scene::CreateEntity(const String& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<IdComponent>();
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		if (name.empty())
		{
			tag.Tag = "New Entity";
		}
		else
		{
			tag.Tag = name;
		}
		std::cout << tag.Tag << "\n";
		return entity;
	}

	void Scene::OnUpdate(float deltaTime)
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<MeshComponent, MaterialComponent>);
		for (auto entity : group)
		{
			auto [transform, mesh, material] = group.get<TransformComponent, MeshComponent, MaterialComponent>(entity);
			Firebox::Renderer3D::DrawMesh(mesh.Mesh, material.Material, transform);
		}
	}
	void Scene::GetAllEntities()
	{
		
	}
}


