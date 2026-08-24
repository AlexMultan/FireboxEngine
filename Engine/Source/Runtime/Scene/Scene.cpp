#include "Scene.h"
#include "Components/CoreComponents.h"
#include "Components/RenderComponents.h"
#include "Components/AnimationComponents.h"
#include "Rendering/Renderer3D.h"
#include "Serialization/SceneSerializer.h"
#include "Entity.h"

#include <fstream>

namespace Firebox {

	Scene::Scene()
	{

	}

	Scene::~Scene()
	{

	}


	Entity Scene::CreateEntity()
	{
		Entity entity = { m_Registry.create(), this };
		return entity;
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

		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		if (entity)
		{
			if (entity.HasComponent<PointLightComponent>()) [[unlikely]]
			{
				Firebox::Renderer3D::DestroyPointLight(entity.GetComponent<PointLightComponent>());
				std::cout << "Destoyed!\n";
			}
			else
				std::cout << "Not Destroyed!\n";

			m_Registry.destroy(entity.GetHandle());
		}
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

		for (auto&& [entity, transform, staticMesh, animator] : m_Registry.view<TransformComponent, StaticMeshComponent, AnimatorComponent>().each())
		{
			animator.Animator->Update(deltaTime);
			const auto& meshes = staticMesh.StaticMesh->GetMeshes();
			const auto& materials = staticMesh.StaticMesh->GetMaterials();

			for (size_t i = 0; i < meshes.size(); i++)
			{
				Renderer3D::DrawMesh(meshes[i], materials[i], transform, animator.Animator);
			}
		}

		for (auto&& [entity, skybox] : m_Registry.view<SkyboxComponent>().each())
		{
			Renderer3D::DrawSkybox(skybox.Skybox);
		}
	}
	void Scene::SaveScene(const String& filename)
	{
		JSON j = *this;
		std::ofstream file(filename);

		if (file.is_open())
		{
			file << j.dump(4);
			file.close();
			FB_CORE_TRACE("Scene successfully saved to: {0}", filename);
		}
		else
			FB_CORE_ERROR("Error: Could not open file for writing: {0}", filename);
	}
	Ref<Scene> Scene::LoadScene(const String& filename)
	{
		std::ifstream file(filename);
		JSON j;

		if (file.is_open())
		{
			file >> j;
			file.close();
			FB_CORE_TRACE("Successfully loaded scene: {0}", filename);
		}
		else
		{
			FB_CORE_ERROR("Error: Could not open file for reading: {0}", filename);
			return nullptr;
		}
		Ref<Scene> scene = CreateRef<Scene>();
		j.get_to(*scene);
		return scene;
	}
}


