#pragma once

#include "Core/CoreMinimal.h"
#include "Scene/Scene.h"
#include "Scene/Entity.h"
#include "ComponentSerializer.h"

namespace nlohmann {

	template<>
	struct adl_serializer<Firebox::Scene>
	{
		static void to_json(JSON& j, const Firebox::Scene& scene)
		{
			j["Scene"] = scene.GetSceneName();

			JSON entitiesJson = JSON::array();
			auto& registry = scene.GetRegistry();
			for (auto handle : registry.view<IdComponent>())
			{
				JSON entityJson = {
					{"Entity", registry.get<IdComponent>(handle).GetId()},
					{"Tag", registry.get<TagComponent>(handle).Tag},
					{"Transform", registry.get<TransformComponent>(handle)}
				};
#if 0
				if (registry.any_of<SkyboxComponent>(handle))
				{
					entityJson["Skybox"] = registry.get<SkyboxComponent>(handle);
				}
#endif
				if (registry.any_of<DirectionalLightComponent>(handle))
					entityJson["Directional Light"] = registry.get<DirectionalLightComponent>(handle);

				if (registry.any_of<PointLightComponent>(handle))
					entityJson["Point Light"] = registry.get<PointLightComponent>(handle);

				if (registry.any_of<SpotLightComponent>(handle))
					entityJson["Spot Light"] = registry.get<SpotLightComponent>(handle);

				if (registry.any_of<StaticMeshComponent>(handle))
					entityJson["Static Mesh"] = registry.get<StaticMeshComponent>(handle);

				if (registry.any_of<PostProcessComponent>(handle))
					entityJson["Post Processing"] = registry.get<PostProcessComponent>(handle);

				entitiesJson.push_back(entityJson);
			}
			j["Entities"] = entitiesJson;
		}

		static void from_json(const JSON& j, Firebox::Scene& scene)
		{
			scene.SetSceneName(j.at("Scene").get<String>());
			
			for (const auto& entityJson : j.at("Entities"))
			{
				Firebox::Entity e = scene.CreateEntity();
				e.AddComponent<IdComponent>(Firebox::UUID(entityJson.at("Entity").get<uint64>()));
				e.AddComponent<TagComponent>(entityJson.at("Tag").get<String>());
				e.AddComponent<TransformComponent>(entityJson.at("Transform").get<TransformComponent>());
#if 0
				if (entityJson.contains("Skybox"))
				{
					e.AddComponent<SkyboxComponent>(entityJson.at("Skybox").get<SkyboxComponent>());
				}
#endif
				if (entityJson.contains("Directional Light"))
					e.AddComponent<DirectionalLightComponent>(entityJson.at("Directional Light").get<DirectionalLightComponent>());

				if (entityJson.contains("Point Light"))
					e.AddComponent<PointLightComponent>(entityJson.at("Point Light").get<PointLightComponent>());

				if (entityJson.contains("Spot Light"))
					e.AddComponent<SpotLightComponent>(entityJson.at("Spot Light").get<SpotLightComponent>());

				if (entityJson.contains("Static Mesh"))
					e.AddComponent<StaticMeshComponent>(entityJson.at("Static Mesh").get<StaticMeshComponent>());

				if (entityJson.contains("Post Processing"))
					e.AddComponent<PostProcessComponent>(entityJson.at("Post Processing").get<PostProcessComponent>());
			}
		}
	};
}