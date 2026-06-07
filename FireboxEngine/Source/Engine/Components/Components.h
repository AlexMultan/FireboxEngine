#pragma once

#include "Engine/Core/Core.h"
#include "Engine/Rendering/Resources/Mesh.h"
#include "Engine/Rendering/Resources/Material.h"

struct TransformComponent
{
	Vector3 Position{ 0.0f, 0.0f, 0.0f };
	Vector3 Rotation{ 0.0f, 0.0f, 0.0f };
	Vector3 Scale{ 1.0f, 1.0f, 1.0f };

	TransformComponent() = default;
	TransformComponent(const TransformComponent&) = default;
	TransformComponent(const Vector3& position, const Vector3& rotation, const Vector3& scale) : Position(position),
		Rotation(rotation), Scale(scale)
	{
	}

	Mat4 GetTransform() const
	{
		Mat4 model = Mat4(1.0f);
		model = glm::translate(model, Position);
		model = glm::rotate(model, glm::radians(Rotation.x), { 1.0f, 0.0f, 0.0f });
		model = glm::rotate(model, glm::radians(Rotation.y), { 0.0f, 0.0f, 1.0f });
		model = glm::rotate(model, glm::radians(Rotation.z), { 0.0f, 1.0f, 0.0f });
		model = glm::scale(model, Scale);
		return model;
	}

	Mat3 GetInverseNormal() const
	{
		return glm::transpose(glm::inverse(Mat3(GetTransform())));
	}
};

struct TagComponent
{
	String Tag;

	TagComponent() = default;
	TagComponent(const TagComponent&) = default;
	TagComponent(const String& tag) : Tag(tag)
	{
	}
};

struct MeshComponent
{
	Ref<Firebox::Mesh> Mesh;
};

struct MaterialComponent
{
	Ref<Firebox::Material> Material;
};