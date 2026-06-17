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
			tag.Tag = "New Entity";
		else
			tag.Tag = name;

		std::cout << tag.Tag << "\n";
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
			//const auto& materials = staticMesh.StaticMesh->GetMaterials();

			for (size_t i = 0; i < meshes.size(); i++)
			{
				//const Ref<Material>& mat = (i < materials.size()) ? materials[i] : Renderer3D::GetDefaultMaterial();
				Renderer3D::DrawMesh(meshes[i], Renderer3D::GetDefaultMaterial(), transform);
			}
		}
	}

	void Scene::GetAllEntities()
	{
		
	}
}


