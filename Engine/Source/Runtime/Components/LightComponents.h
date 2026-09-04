#pragma once

#include "Core/CoreMinimal.h"

struct DirectionalLightComponent
{
	Vector3 Color{ 1.0f, 0.89f, 0.96f };
	Vector3 Direction{ -0.2f, -1.0f, -0.3f };
	float Intensity = 5.0f;

	DirectionalLightComponent() = default;
	DirectionalLightComponent(const DirectionalLightComponent&) = default;
	DirectionalLightComponent(const Vector3& color, const Vector3& direction, float intensity) : Color(color), Direction(direction), Intensity(intensity)
	{
	}
};

struct PointLightComponent
{
	Vector3 Position{ 0.0f, 0.0f, 0.0f };
	Vector3 Color{ 1.0f, 0.89f, 0.96f };
	float Constant = 1.0f;
	float Linear = 0.09f;
	float Quadratic = 0.032f;

	PointLightComponent() = default;
	PointLightComponent(const PointLightComponent&) = default;
	PointLightComponent(const Vector3& position, const Vector3& color, const float constant, const float quadratic)
		: Position(position), Color(color), Constant(constant), Quadratic(quadratic)
	{
	}

	bool operator==(const PointLightComponent& other) const
	{
		std::cout << "True\n";
		return this == &other;
	}

	bool operator!=(const PointLightComponent& other) const
	{
		std::cout << "False\n";
		return this != &other;
	}
};

struct SpotLightComponent
{
	Vector3 Position{ 0.0f, 0.0f, 0.0f };
	Vector3 Direction{ 0.0f, 0.0f, 0.0f };
	Vector3 Color{ 1.0f, 0.89f, 0.96f };
	float Constant = 1.0f;
	float Linear = 0.09f;
	float Quadratic = 0.032f;
	float CutOff = 15.0f;
	float OuterCutOff = 25.0f;

	SpotLightComponent() = default;
	SpotLightComponent(const SpotLightComponent&) = default;
	SpotLightComponent(const Vector3& position, const Vector3& direction, const Vector3& color, const float constant, const float quadratic, const float cutOff,
		const float outerCutOff)
		: Position(position), Direction(direction), Color(color), Constant(constant), Quadratic(quadratic), CutOff(cutOff), OuterCutOff(outerCutOff)
	{
	}
};