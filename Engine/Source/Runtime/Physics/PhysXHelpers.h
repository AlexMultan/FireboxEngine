#pragma once

#include "Components/CoreComponents.h"

#include <physx/include/PxPhysicsAPI.h>

physx::PxTransform ConvertToPxTransform(const TransformComponent& transform)
{
	glm::quat glmQ(glm::radians(transform.Rotation));
	physx::PxQuat physxQ(glmQ.x, glmQ.y, glmQ.z, glmQ.w);

	return physx::PxTransform({ transform.Position.x, transform.Position.y, transform.Position.z}, physxQ);
}