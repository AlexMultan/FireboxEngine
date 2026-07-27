#pragma once

#include "Core/Core.h"
#include "Rendering/Geometry/StaticMesh.h"
#include "Animation/Animator.h"

struct AnimatorComponent
{
	Ref<Firebox::Animator> Animator;

	AnimatorComponent() = default;
	AnimatorComponent(const AnimatorComponent&) = default;
	AnimatorComponent(const Ref<Firebox::Animator>& animator)
		: Animator(animator)
	{
	}
};