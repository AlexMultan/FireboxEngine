#pragma once

#include "Engine/Core/Core.h"

namespace Firebox {

	struct DirectionalLightComponent
	{
		Vector3 Color{ 1.0f, 1.0f, 1.0f };
		Vector3 Direction{ 0.0f, 0.0f, 0.0f };
	};
}