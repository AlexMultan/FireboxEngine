#pragma once

#include "Core/Core.h"
#include "Scene/Scene.h"
#include "Scene/Entity.h"
#include "ComponentSerializer.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace nlohmann {

	template<>
	struct adl_serializer<Firebox::Entity>
	{
		static void to_json(json& j, const Firebox::Entity& entity)
		{
			j = json{
				{"Entity", entity.GetComponent<IdComponent>().GetId()},
				{"Name", entity.GetComponent<TagComponent>()},
				{"Transform", entity.GetComponent<TransformComponent>()}
			};
		}

		static void from_json(const json& j, Firebox::Entity& entity)
		{
			entity.AddComponent<IdComponent>(j.at("Entity").get<uint64>());
			entity.AddComponent<TagComponent>(j.at("Tag").get<TagComponent>());
			entity.AddComponent<TransformComponent>(j.at("Transform").get<TransformComponent>());
		}
	};

	template<>
	struct adl_serializer<Firebox::Scene>
	{
		static void to_json(json& j, const Firebox::Scene& scene)
		{
			j = json{
				"Scene", scene.GetSceneName()
				//"Entities", scene.GetAllEntities()
			};
		}

		static void from_json(const json& j, Firebox::Scene& scene)
		{
			scene.SetSceneName(j.at("Scene").get<String>());
			//scene.SetEntities(j.at("Entities").get<DynamicArray<Firebox::Entity>>());
		}
	};
}