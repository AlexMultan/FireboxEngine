#pragma once

#include "Core/Core.h"
#include "Core/CoreMinimal.h"

#include <physx/include/PxPhysicsAPI.h>

using namespace physx;

namespace Firebox {

	class FIREBOX_API Physics3D
	{
	public:
		using PreStepCallback = std::function<void(float fixedDeltaTime)>;

		static bool Init(bool enablePvd = false, const char* pvdHost = "127.0.0.1");
		static int Update(float deltaTime, const PreStepCallback& beforeStep = {});
		static void Cleanup();
		static bool IsInitialized() noexcept;

		static Vector3& GetGravity() noexcept;
		static void SetGravity(const Vector3& gravity);

		static PxPhysics* GetPhysics() noexcept;
		static PxScene* GetScene() noexcept;
		static PxMaterial* GetMaterial() noexcept;

		static void AddActor(PxActor& actor);
		static void RemoveActor(PxActor& actor);

		static float GetFixedTimeStep() noexcept;

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
		static PxPvdTransport*			s_PvdTransport;
		static bool						s_ExtenstionsInitialized;

		// Custom properties
		static Vector3 s_Gravity;
		static float s_Accumulator;
	};
}