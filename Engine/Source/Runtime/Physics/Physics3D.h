#pragma once

#include "Core/Core.h"
#include "Core/CoreMinimal.h"

#include <physx/include/PxPhysicsAPI.h>

using namespace physx;

namespace Firebox {

	class FIREBOX_API Physics3D
	{
	public:
		static void Init();
		static void Update(float deltaTime);
		static void Cleanup();

		static Vector3& GetGravity();
		static void SetGravity(const Vector3& gravity);

		static PxPhysics* GetPhysics();
		static PxScene* GetScene();
		static PxMaterial* GetMaterial();

		static void AddActor(PxActor& actor);
		static void RemoveActor(PxActor& actor);

	private:
		// PhysX properties
		static PxDefaultAllocator		s_Allocator;
		static PxDefaultErrorCallback	s_ErrorCallback;
		static PxFoundation*			s_Foundation;
		static PxPhysics*				s_Physics;
		static PxDefaultCpuDispatcher*	s_Dispacher;
		static PxScene*					s_Scene;
		static PxMaterial*				s_Material;
		static PxPvd*					s_Pvd;

		// Custom properties
		static Vector3 s_Gravity;
	};
}