#include "BoxCollider.h"
#include "Physics/PhysXHelpers.h"

void Firebox::BoxCollider::CreateBoxCollider(PxPhysics* physics, PxScene* scene, const TransformComponent& transform, const Vector3& size, bool isStatic)
{
	if (!physics || !scene) return;

	m_Material = physics->createMaterial(0.5f, 0.5f, 0.6f);
	if (!m_Material) return;

	PxBoxGeometry geometry{ size.x / 2, size.y / 2, size.z / 2 };

	m_Shape = physics->createShape(geometry, *m_Material, true);
	if (!m_Shape) return;

	if (isStatic)
	{
		m_Body = physics->createRigidStatic(ConvertToPxTransform(transform));
	}
	else
	{
		PxRigidDynamic* dynamicBody = physics->createRigidDynamic(ConvertToPxTransform(transform));
		PxRigidBodyExt::updateMassAndInertia(*dynamicBody, 10.0f);
		m_Body = dynamicBody;
	}

	if (m_Body)
	{
		m_Body->attachShape(*m_Shape);
		scene->addActor(*m_Body);
	}
}

void Firebox::BoxCollider::Synchronize(const TransformComponent& transform)
{
	if (!m_Body || !m_Shape) return;

	PxVec3 baseHalfExtent = { 0.5f, 0.5f, 0.5f };
	PxVec3 newHalfExtent = { baseHalfExtent.x * transform.Scale.x, baseHalfExtent.y * transform.Scale.y, baseHalfExtent.z * transform.Scale.z };
	m_Shape->setGeometry(PxBoxGeometry(newHalfExtent));

	PxTransform newPose = ConvertToPxTransform(transform);

	if (m_Body->is<PxRigidDynamic>() && m_Body->is<PxRigidDynamic>()->getRigidBodyFlags() & PxRigidBodyFlag::eKINEMATIC)
		m_Body->is<PxRigidDynamic>()->setKinematicTarget(newPose);
	else
		m_Body->setGlobalPose(newPose);
}

Firebox::BoxCollider::~BoxCollider()
{
	/*if (m_Body && m_Shape)
		m_Body->detachShape(*m_Shape);

	if (m_Shape)
		m_Shape->release();

	if (m_Body)
		m_Body->release();

	if (m_Material)
		m_Material->release();*/
}

void Firebox::BoxCollider::UpdateBoxSize(const Vector3& newSize)
{
	if (m_Shape)
	{
		PxBoxGeometry newGeometry{ newSize.x / 2, newSize.y / 2, newSize.z / 2 };
		m_Shape->setGeometry(newGeometry);
	}
}
