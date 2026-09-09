#include "BoxCollider.h"
#include "Physics/PhysXHelpers.h"

void Firebox::BoxCollider::CreateBoxCollider(PxPhysics* physics, PxScene* scene, const TransformComponent& transform, const Vector3& size, bool isStatic)
{
	if (!physics || !scene) return;

	m_Material = physics->createMaterial(0.5f, 0.5f, 0.6f);
	if (!m_Material) return;

	PxBoxGeometry geometry{ size.x / 2, size.y / 2, size.z / 2 };

	m_Shape = physics->createShape(geometry, *m_Material, true);
	m_Shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, true);
	m_Shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, false);
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

void Firebox::BoxCollider::Synchronize(TransformComponent& transform, bool isStatic)
{
	if (!m_Body) return;

	if (isStatic)
	{
		PxRigidStatic* staticBody = m_Body->is<PxRigidStatic>();

		if (staticBody)
		{
			PxTransform physxPose = m_Body->getGlobalPose();
			transform.Position = {
				physxPose.p.x,
				physxPose.p.y,
				physxPose.p.z
			};
			transform.Rotation = ConvertPxQuatToRotation(physxPose.q);
		}
	}
	else
	{
		PxRigidDynamic* dynamicBody = m_Body->is<PxRigidDynamic>();

		if (dynamicBody)
		{
			if (dynamicBody->getRigidBodyFlags() & PxRigidBodyFlag::eKINEMATIC)
			{
				PxTransform newPose = ConvertToPxTransform(transform);
				dynamicBody->setKinematicTarget(newPose);
			}
			else
			{
				PxTransform physxPose = m_Body->getGlobalPose();
				transform.Position = {
					physxPose.p.x,
					physxPose.p.y,
					physxPose.p.z
				};
				transform.Rotation = ConvertPxQuatToRotation(physxPose.q);
			}
		}
	}
}

Firebox::BoxCollider::~BoxCollider()
{
	
}

void Firebox::BoxCollider::UpdateBoxSize(const Vector3& newSize)
{
	if (m_Shape)
	{
		PxBoxGeometry newGeometry{ newSize.x / 2, newSize.y / 2, newSize.z / 2 };
		m_Shape->setGeometry(newGeometry);
	}
}