#pragma once

#include "Core/Core.h"
#include "Rendering/Geometry/Mesh.h"

struct MeshComponent
{
	Ref<Firebox::Mesh> Mesh;

	MeshComponent() = default;
	MeshComponent(const MeshComponent&) = default;
	MeshComponent(const Ref<Firebox::Mesh>& mesh)
		: Mesh(mesh)
	{
	}

	MeshComponent(const std::vector<Firebox::Vertex>& vertices, const std::vector<uint32_t>& indices)
		: Mesh(CreateRef<Firebox::Mesh>(vertices, indices))
	{
	}
};