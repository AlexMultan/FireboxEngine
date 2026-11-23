#pragma once

#include "Components/CoreComponents.h"

#include <physx/include/PxPhysicsAPI.h>

inline physx::PxTransform ConvertToPxTransform(const TransformComponent& transform)
{
    const glm::quat q = glm::normalize(
        glm::quat(glm::radians(transform.Rotation)));

    return physx::PxTransform(
        physx::PxVec3(transform.Position.x,
            transform.Position.y,
            transform.Position.z),
        physx::PxQuat(q.x, q.y, q.z, q.w));
}

inline Vector3 ConvertPxQuatToRotation(const PxQuat& rotation)
{
    const glm::quat q = glm::normalize(
        glm::quat(rotation.w, rotation.x, rotation.y, rotation.z));

    return glm::degrees(glm::eulerAngles(q));
}