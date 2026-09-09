#pragma once

#include "Physics/Physics3D.h"

namespace Firebox {

	class FIREBOX_API Rigidbody : public RefCounted
	{
	public:
		Rigidbody();
		~Rigidbody();

	private:
		PxRigidDynamic* m_BodyDynamic = nullptr;
	};
}