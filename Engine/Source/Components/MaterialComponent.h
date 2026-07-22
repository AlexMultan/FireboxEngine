#pragma once

#include "Core/Core.h"
#include "Rendering/Materials/Material.h"

struct MaterialComponent
{
	Ref<Firebox::Material> Material;

	MaterialComponent() = default;
	MaterialComponent(const MaterialComponent&) = default;
	MaterialComponent(const Ref<Firebox::Material>& material)
		: Material(material)
	{
	}
};