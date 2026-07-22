#pragma once

#include "Core/Core.h"
#include "Core/UUID.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct IdComponent
{
private:
	Firebox::UUID m_Id;

public:
	IdComponent() = default;
	IdComponent(const IdComponent&) = default;
	IdComponent(Firebox::UUID id) { m_Id = id; }

	uint64 GetId() const { return m_Id; }
};

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
		model = glm::rotate(model, glm::radians(Rotation.z), { 0.0f, 0.0f, 1.0f });
		model = glm::rotate(model, glm::radians(Rotation.y), { 0.0f, 1.0f, 0.0f });
		model = glm::rotate(model, glm::radians(Rotation.x), { 1.0f, 0.0f, 0.0f });
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


