#pragma once

#include "Core/Core.h"
#include "Scene/Scene.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace Firebox::Serialize {

	class FIREBOX_API SceneSerializer
	{
	public:
		SceneSerializer();
		~SceneSerializer();

		void Serialize(json& j, const Scene& scene);
		json Deserialize(const json& j, Scene& scene);
	};
}