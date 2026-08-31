#pragma once

#include "Core/Core.h"

#include <physx/include/PxPhysicsAPI.h>

using namespace physx;

namespace Firebox {

	class FIREBOX_API Physics3D
	{
	public:
		Physics3D();
		~Physics3D();

		void Init();
		void Update(float deltaTime);
		void Cleanup();

		static Vector3& GetGravity();
		static void SetGravity(const Vector3& gravity);

	private:
		PxDefaultAllocator m_Allocator;
		PxDefaultErrorCallback m_ErrorCallback;
		PxFoundation* m_Foundation = nullptr;
		PxPhysics* m_Physics = nullptr;
		PxDefaultCpuDispatcher* m_Dispacher = nullptr;
		PxScene* m_Scene = nullptr;
		PxMaterial* m_Material = nullptr;
		PxPvd* m_Pvd = nullptr;

		static Vector3 m_Gravity;
	};
}