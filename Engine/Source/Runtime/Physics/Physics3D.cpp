#include "Physics3D.h"
#include "Core/Log.h"
#include "Utils/Assert.h"

#include <physx/snippets/snippetcommon/SnippetPVD.h>
#include <physx/snippets/snippetcommon/SnippetPrint.h>

PxDefaultAllocator		Firebox::Physics3D::s_Allocator;
PxDefaultErrorCallback	Firebox::Physics3D::s_ErrorCallback;
PxFoundation*			Firebox::Physics3D::s_Foundation = nullptr;
PxPhysics*				Firebox::Physics3D::s_Physics = nullptr;
PxDefaultCpuDispatcher* Firebox::Physics3D::s_Dispacher = nullptr;
PxScene*				Firebox::Physics3D::s_Scene = nullptr;
PxMaterial*				Firebox::Physics3D::s_Material = nullptr;
PxPvd*					Firebox::Physics3D::s_Pvd = nullptr;

Vector3		Firebox::Physics3D::s_Gravity{ 0.0f, -9.81f, 0.0f };
Vector3&	Firebox::Physics3D::GetGravity()					   { return s_Gravity; }
void		Firebox::Physics3D::SetGravity(const Vector3& gravity) { s_Gravity = gravity; }

PxPhysics*	Firebox::Physics3D::GetPhysics()	{ return s_Physics; }
PxScene*	Firebox::Physics3D::GetScene()		{ return s_Scene; }
PxMaterial*	Firebox::Physics3D::GetMaterial()	{ return s_Material; }

void Firebox::Physics3D::Init()
{
	s_Foundation = PxCreateFoundation(PX_PHYSICS_VERSION, s_Allocator, s_ErrorCallback);
	FB_ASSERT(s_Foundation, "Assertion Failed: Physics foundation is not valid!")

	s_Pvd = PxCreatePvd(*s_Foundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	s_Pvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	s_Physics = PxCreatePhysics(PX_PHYSICS_VERSION, *s_Foundation, PxTolerancesScale(), true, s_Pvd);

	PxSceneDesc sceneDesc(s_Physics->getTolerancesScale());
	sceneDesc.gravity = { s_Gravity.x, s_Gravity.y, s_Gravity.z };
	s_Dispacher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = s_Dispacher;
	sceneDesc.filterShader = PxDefaultSimulationFilterShader;
	s_Scene = s_Physics->createScene(sceneDesc);

	PxPvdSceneClient* pvdClient = s_Scene->getScenePvdClient();
	if (pvdClient)
	{
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}
	s_Material = s_Physics->createMaterial(0.5f, 0.5f, 0.6f);
}

void Firebox::Physics3D::Update(float deltaTime)
{
	s_Scene->simulate(deltaTime);
	s_Scene->fetchResults(true);
}

void Firebox::Physics3D::Cleanup()
{
	PX_RELEASE(s_Scene);
	PX_RELEASE(s_Dispacher);
	PX_RELEASE(s_Physics);

	if (s_Pvd)
	{
		PxPvdTransport* transport = s_Pvd->getTransport();
		PX_RELEASE(s_Pvd);
		PX_RELEASE(transport);
	}
	PX_RELEASE(s_Foundation);
}

void Firebox::Physics3D::AddActor(PxActor& actor)
{
	s_Scene->addActor(actor);
	FB_CORE_TRACE("Added actor to the physics scene");
}

void Firebox::Physics3D::RemoveActor(PxActor& actor)
{
	s_Scene->removeActor(actor);
}