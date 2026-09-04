#pragma once

#include "Core/Core.h"
#include "Core/CoreMinimal.h"
#include "Components/CoreComponents.h"

#include <physx/include/PxPhysicsAPI.h>

using namespace physx;

namespace Firebox {

	class FIREBOX_API BoxCollider : public RefCounted
	{
	public:
		BoxCollider() = default;
		void CreateBoxCollider(PxPhysics* physics, PxScene* scene, const TransformComponent& transform, const Vector3& size, bool isStatic);
		void Synchronize(const TransformComponent& transform);
		~BoxCollider();

		inline PxRigidActor& GetBody() { return *m_Body; }

		void UpdateBoxSize(const Vector3& newSize);

	private:
		PxShape*		m_Shape = nullptr;
		PxRigidActor*	m_Body = nullptr;
		PxMaterial*		m_Material = nullptr;
	};
}