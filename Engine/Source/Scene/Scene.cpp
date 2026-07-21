#include "Scene.h"
#include "Components/Components.h"
#include "Rendering/Renderer3D.h"
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
			tag.Tag = m_DefaultEntityTag;
		else
			tag.Tag = name;

		m_SceneEntities.emplace_back(entity);
		return entity;
	}

	void Scene::OnUpdate(float deltaTime)
	{
		for (auto&& [entity, transform, mesh, material] : m_Registry.view<TransformComponent, MeshComponent, MaterialComponent>().each())
		{
			Renderer3D::DrawMesh(mesh.Mesh, material.Material, transform);
		}

		for (auto&& [entity, transform, staticMesh] : m_Registry.view<TransformComponent, StaticMeshComponent>().each())
		{
			const auto& meshes = staticMesh.StaticMesh->GetMeshes();
			const auto& materials = staticMesh.StaticMesh->GetMaterials();

			for (size_t i = 0; i < meshes.size(); i++)
			{
				Renderer3D::DrawMesh(meshes[i], materials[i], transform);
			}
		}
	}
}


