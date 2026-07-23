#pragma once

#include "Components/Components.h"
#include "JsonAlias.h"

namespace nlohmann {

	template<>
	struct adl_serializer<Vector3>
	{
		static void to_json(JSON& j, const Vector3& v)
		{
			j = JSON{ {"X", v.x}, {"Y", v.y}, {"Z", v.z} };
		}

		static void from_json(const JSON& j, Vector3& v)
		{
			j.at("X").get_to(v.x);
			j.at("Y").get_to(v.y);
			j.at("Z").get_to(v.z);
		}
	};

	template<>
	struct adl_serializer<TransformComponent>
	{
		static void to_json(JSON& j, const TransformComponent& transform)
		{
			j = JSON{
				{"Position", transform.Position},
				{"Rotation", transform.Rotation},
				{"Scale", transform.Scale}
			};
		}

		static void from_json(const JSON& j, TransformComponent& transform)
		{
			j.at("Position").get_to(transform.Position);
			j.at("Rotation").get_to(transform.Rotation);
			j.at("Scale").get_to(transform.Scale);
		}
	};

	template<>
	struct adl_serializer<TagComponent>
	{
		static void to_json(JSON& j, const TagComponent& tag)
		{
			j = JSON{ "Tag", tag.Tag };
		}

		static void from_json(const JSON& j, TagComponent& tag)
		{
			j.at("Tag").get_to(tag.Tag);
		}
	};
}