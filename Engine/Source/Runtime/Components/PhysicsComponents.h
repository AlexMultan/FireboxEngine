#pragma once

#include "Core/Core.h"

struct BoxColliderComponent
{
	BoxColliderComponent() = default;
	BoxColliderComponent(const BoxColliderComponent&) = default;
};

struct SphereColliderComponent
{
	SphereColliderComponent() = default;
	SphereColliderComponent(const SphereColliderComponent&) = default;
};

struct CapsuleColliderComponent
{
	CapsuleColliderComponent() = default;
	CapsuleColliderComponent(const CapsuleColliderComponent&) = default;
};

struct ConvexColliderComponent
{
	ConvexColliderComponent() = default;
	ConvexColliderComponent(const ConvexColliderComponent&) = default;
};

struct RigidbodyComponent
{
	RigidbodyComponent() = default;
	RigidbodyComponent(const RigidbodyComponent&) = default;
};