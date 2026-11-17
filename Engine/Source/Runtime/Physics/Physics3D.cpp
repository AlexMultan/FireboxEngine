#include "Physics3D.h"
#include "Core/Log.h"
#include "Utils/Assert.h"

#include <physx/snippets/snippetcommon/SnippetPVD.h>
#include <physx/snippets/snippetcommon/SnippetPrint.h>

namespace {
	constexpr float k_FixedStep = 1.0f / 60.0f;
	constexpr int k_MaxSubstepPerFrame = 8;
}

PxDefaultAllocator		Firebox::Physics3D::s_Allocator;
PxDefaultErrorCallback	Firebox::Physics3D::s_ErrorCallback;
PxFoundation*			Firebox::Physics3D::s_Foundation = nullptr;
PxPhysics*				Firebox::Physics3D::s_Physics = nullptr;
PxDefaultCpuDispatcher* Firebox::Physics3D::s_Dispacher = nullptr;
PxScene*				Firebox::Physics3D::s_Scene = nullptr;
PxMaterial*				Firebox::Physics3D::s_Material = nullptr;
PxPvd*					Firebox::Physics3D::s_Pvd = nullptr;
PxPvdTransport*			Firebox::Physics3D::s_PvdTransport = nullptr;
bool					Firebox::Physics3D::s_ExtenstionsInitialized = false;

Vector3		Firebox::Physics3D::s_Gravity{ 0.0f, -9.81f, 0.0f };
float		Firebox::Physics3D::s_Accumulator = 0.0f;

Vector3&	Firebox::Physics3D::GetGravity() noexcept	{ return s_Gravity; }

void Firebox::Physics3D::SetGravity(const Vector3& gravity)
{
	if (!std::isfinite(gravity.x) || !std::isfinite(gravity.y) || !std::isfinite(gravity.z)) return;

	s_Gravity = gravity;
	if (s_Scene) s_Scene->setGravity(PxVec3(gravity.x, gravity.y, gravity.z));
}

PxPhysics*	Firebox::Physics3D::GetPhysics() noexcept	{ return s_Physics; }
PxScene*	Firebox::Physics3D::GetScene() noexcept		{ return s_Scene; }
PxMaterial*	Firebox::Physics3D::GetMaterial() noexcept	{ return s_Material; }
float Firebox::Physics3D::GetFixedTimeStep() noexcept	{ return k_FixedStep; }

bool Firebox::Physics3D::IsInitialized() noexcept
{
	return s_Foundation && s_Physics && s_Scene && s_Material;
}

bool Firebox::Physics3D::Init(bool enablePvd, const char* pvdHost)
{
	if (IsInitialized())
		return true;

	Cleanup();

	s_Foundation = PxCreateFoundation(PX_PHYSICS_VERSION, s_Allocator, s_ErrorCallback);
	FB_ASSERT(s_Foundation, "Assertion Failed: Physics foundation is not valid!");
	if (!s_Foundation) return false;

	if (enablePvd)
	{
		s_Pvd = PxCreatePvd(*s_Foundation);
		if (s_Pvd)
		{
			const char* host = pvdHost ? pvdHost : "127.0.0.1";
			s_PvdTransport = PxDefaultPvdSocketTransportCreate(host, 5425, 100);

			if (!s_PvdTransport || !s_Pvd->connect(*s_PvdTransport, PxPvdInstrumentationFlag::eALL))
			{
				PX_RELEASE(s_Pvd);
				PX_RELEASE(s_PvdTransport);
			}
		}
	}

	s_Physics = PxCreatePhysics(PX_PHYSICS_VERSION, *s_Foundation, PxTolerancesScale(), true, s_Pvd);
	if (!s_Physics)
	{
		Cleanup();
		return false;
	}

	if (!PxInitExtensions(*s_Physics, s_Pvd))
	{
		Cleanup();
		return false;
	}
	s_ExtenstionsInitialized = true;

	PxSceneDesc sceneDesc(s_Physics->getTolerancesScale());
	sceneDesc.gravity = { s_Gravity.x, s_Gravity.y, s_Gravity.z };
	s_Dispacher = PxDefaultCpuDispatcherCreate(2);
	if (!s_Dispacher)
	{
		Cleanup();
		return false;
	}
	sceneDesc.cpuDispatcher = s_Dispacher;
	sceneDesc.filterShader = PxDefaultSimulationFilterShader;
	s_Scene = s_Physics->createScene(sceneDesc);
	if (!s_Scene)
	{
		Cleanup();
		return false;
	}

	s_Material = s_Physics->createMaterial(0.5f, 0.5f, 0.6f);
	if (!s_Material)
	{
		Cleanup();
		return false;
	}

	if (s_Pvd)
	{
		PxPvdSceneClient* pvdClient = s_Scene->getScenePvdClient();
		if (pvdClient)
		{
			pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
			pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
			pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
		}
	}

	s_Accumulator = 0.0f;
	return true;
}

int Firebox::Physics3D::Update(float deltaTime, const PreStepCallback& beforeStep)
{
	if (!IsInitialized() || std::isfinite(deltaTime) || deltaTime <= 0.0f) return 0;

	const float maxCatchUp = k_FixedStep * k_MaxSubstepPerFrame;
	s_Accumulator = std::min(s_Accumulator + deltaTime, maxCatchUp);

	int steps = 0;
	while (steps < k_MaxSubstepPerFrame && s_Accumulator >= k_FixedStep)
	{
		if (beforeStep)
			beforeStep(k_FixedStep);
		
		s_Scene->simulate(k_FixedStep);
		s_Scene->fetchResults(true);
		s_Accumulator -= k_FixedStep;
		++steps;
	}
	return steps;
}

void Firebox::Physics3D::Cleanup()
{
	PX_RELEASE(s_Material);
	PX_RELEASE(s_Scene);
	PX_RELEASE(s_Dispacher);
	if (s_ExtenstionsInitialized) 
	{
		PxCloseExtensions();
		s_ExtenstionsInitialized = false;
	}
	PX_RELEASE(s_Physics);
	PX_RELEASE(s_Pvd);
	PX_RELEASE(s_PvdTransport);
	PX_RELEASE(s_Foundation);
	s_Accumulator = 0.0f;
}

void Firebox::Physics3D::AddActor(PxActor& actor)
{
	if (s_Scene && !actor.getScene())
		s_Scene->addActor(actor);
}

void Firebox::Physics3D::RemoveActor(PxActor& actor)
{
	if (s_Scene && actor.getScene() == s_Scene)
		s_Scene->removeActor(actor);
}