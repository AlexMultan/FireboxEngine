#pragma once

#include "Components/Components.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace nlohmann {

	template<>
	struct adl_serializer<Vector3>
	{
		static void to_json(json& j, const Vector3& v)
		{
			j = json{ {"X", v.x}, {"Y", v.y}, {"Z", v.z} };
		}

		static void from_json(const json& j, Vector3& v)
		{
			j.at("X").get_to(v.x);
			j.at("Y").get_to(v.y);
			j.at("Z").get_to(v.z);
		}
	};

	template<>
	struct adl_serializer<TransformComponent>
	{
		static void to_json(json& j, const TransformComponent& transform)
		{
			j = json{
				{"Position", transform.Position},
				{"Rotation", transform.Rotation},
				{"Scale", transform.Scale}
			};
		}

		static void from_json(const json& j, TransformComponent& transform)
		{
			j.at("Position").get_to(transform.Position);
			j.at("Rotation").get_to(transform.Rotation);
			j.at("Scale").get_to(transform.Scale);
		}
	};

	template<>
	struct adl_serializer<TagComponent>
	{
		static void to_json(json& j, const TagComponent& tag)
		{
			j = json{ "Tag", tag };
		}

		static void from_json(const json& j, TagComponent& tag)
		{
			j.at("Tag").get_to(tag);
		}
	};

	template<>
	struct adl_serializer<IdComponent>
	{
		static void to_json(json& j, const IdComponent& id)
		{
			j = json{ "Entity", id };
		}

		static void from_json(const json& j, IdComponent& id)
		{
			j.at("Entity").get_to(id);
		}
	};
}