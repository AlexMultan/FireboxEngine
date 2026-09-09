#pragma once

#include "Physics/Physics3D.h"

namespace Firebox {

	class FIREBOX_API ConvexCollider : public RefCounted
	{
	public:
		ConvexCollider();
		~ConvexCollider();

	private:
		PxShape* m_Shape = nullptr;
		PxTransform m_Transform{};
		PxRigidStatic* m_Body = nullptr;
		Vector3 m_Size{};
	};
}