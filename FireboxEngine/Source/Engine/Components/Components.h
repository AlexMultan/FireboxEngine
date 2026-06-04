#pragma once

#include "Engine/Core/Core.h"
//#include "Engine/Rendering/Camera/Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Firebox {
	struct TransformComponent
	{
		Vector3 Position{ 0.0f, 0.0f, 0.0f };
		Vector3 Rotation{ 0.0f, 0.0f, 0.0f };
		Vector3 Scale{ 1.0f, 1.0f, 1.0f };

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
	};
}