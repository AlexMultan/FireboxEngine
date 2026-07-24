#pragma once

#include "Core/Core.h"
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

				if (registry.any_of<SkyboxComponent>(handle))
				{
					entityJson["Skybox"] = registry.get<SkyboxComponent>(handle);
				}

				if (registry.any_of<SkyboxComponent>(handle))
				{
					entityJson["Directional Light"] = registry.get<DirectionalLightComponent>(handle);
				}

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

				if (entityJson.contains("Skybox"))
				{
					e.AddComponent<SkyboxComponent>(entityJson.at("Skybox").get<SkyboxComponent>());
				}

				if (entityJson.contains("Directional Light"))
				{
					e.AddComponent<DirectionalLightComponent>(entityJson.at("Directional Light").get<DirectionalLightComponent>());
				}
			}
		}
	};
}