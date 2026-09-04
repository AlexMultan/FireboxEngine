#pragma once

#include "Core/CoreMinimal.h"
#include "Physics/Collision/BoxCollider.h"
#include "Physics/Collision/SphereCollider.h"
#include "Physics/Collision/CapsuleCollider.h"
#include "Physics/Collision/ConvexCollider.h"
#include "Physics/Simulation/Rigidbody.h"

struct BoxColliderComponent
{
	Ref<Firebox::BoxCollider> Collider;
	Vector3 Size = { 1.0f, 1.0f, 1.0f };

	BoxColliderComponent() = default;
	BoxColliderComponent(const BoxColliderComponent&) = default;
	BoxColliderComponent(const Ref<Firebox::BoxCollider>& collider) : Collider(collider)
	{
	}
};

struct SphereColliderComponent
{
	Ref<Firebox::SphereCollider> Collider;

	SphereColliderComponent() = default;
	SphereColliderComponent(const SphereColliderComponent&) = default;
};

struct CapsuleColliderComponent
{
	Ref<Firebox::CapsuleCollider> Collider;

	CapsuleColliderComponent() = default;
	CapsuleColliderComponent(const CapsuleColliderComponent&) = default;
};

struct ConvexColliderComponent
{
	Ref<Firebox::ConvexCollider> Collider;

	ConvexColliderComponent() = default;
	ConvexColliderComponent(const ConvexColliderComponent&) = default;
};

struct RigidbodyComponent
{
	Ref<Firebox::Rigidbody> Body;

	RigidbodyComponent() = default;
	RigidbodyComponent(const RigidbodyComponent&) = default;
};