#pragma once

#include "Core/Core.h"

struct DirectionalLightComponent
{
	Vector3 Color{ 1.0f, 0.89f, 0.96f };
	Vector3 Direction{ -0.2f, -1.0f, -0.3f };

	DirectionalLightComponent() = default;
	DirectionalLightComponent(const DirectionalLightComponent&) = default;
	DirectionalLightComponent(const Vector3& color, const Vector3& direction) : Color(color), Direction(direction) {}
};