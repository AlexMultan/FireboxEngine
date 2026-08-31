#include "Physics3D.h"
#include "Core/Log.h"
#include "Utils/Assert.h"

#include <physx/snippets/snippetcommon/SnippetPVD.h>
#include <physx/snippets/snippetcommon/SnippetPrint.h>

Vector3 Firebox::Physics3D::m_Gravity{ 0.0f, -9.81f, 0.0f };
Vector3& Firebox::Physics3D::GetGravity() { return m_Gravity; }
void Firebox::Physics3D::SetGravity(const Vector3& gravity) { m_Gravity = gravity; }

Firebox::Physics3D::Physics3D()
{

}

Firebox::Physics3D::~Physics3D()
{

}

void Firebox::Physics3D::Init()
{
	m_Foundation = PxCreateFoundation(PX_PHYSICS_VERSION, m_Allocator, m_ErrorCallback);
	FB_ASSERT(m_Foundation, "Assertion Failed: Physics foundation is not valid!")

	m_Pvd = PxCreatePvd(*m_Foundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	m_Pvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	m_Physics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_Foundation, PxTolerancesScale(), true, m_Pvd);

	PxSceneDesc sceneDesc(m_Physics->getTolerancesScale());
	sceneDesc.gravity = { m_Gravity.x, m_Gravity.y, m_Gravity.z };
	m_Dispacher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = m_Dispacher;
	sceneDesc.filterShader = PxDefaultSimulationFilterShader;
	m_Scene = m_Physics->createScene(sceneDesc);

	PxPvdSceneClient* pvdClient = m_Scene->getScenePvdClient();
	if (pvdClient)
	{
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}
	m_Material = m_Physics->createMaterial(0.5f, 0.5f, 0.6f);
}

void Firebox::Physics3D::Update(float deltaTime)
{
	m_Scene->simulate(deltaTime);
	m_Scene->fetchResults(true);
}

void Firebox::Physics3D::Cleanup()
{
	PX_RELEASE(m_Scene);
	PX_RELEASE(m_Dispacher);
	PX_RELEASE(m_Physics);

	if (m_Pvd)
	{
		PxPvdTransport* transport = m_Pvd->getTransport();
		PX_RELEASE(m_Pvd);
		PX_RELEASE(transport);
	}
	PX_RELEASE(m_Foundation);
}
