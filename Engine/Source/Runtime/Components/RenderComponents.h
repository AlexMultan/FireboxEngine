#pragma once

#include "Core/Core.h"
#include "Rendering/Geometry/Mesh.h"
#include "Rendering/Materials/Material.h"
#include "Rendering/Geometry/StaticMesh.h"
#include "Rendering/Skybox/Skybox.h"

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

struct StaticMeshComponent
{
	Ref<Firebox::StaticMesh> StaticMesh;

	StaticMeshComponent() = default;
	StaticMeshComponent(const StaticMeshComponent&) = default;
	StaticMeshComponent(const Ref<Firebox::StaticMesh>& staticMesh)
		: StaticMesh(staticMesh)
	{
	}
};

struct SkyboxComponent
{
	Ref<Firebox::Skybox> Skybox;

	SkyboxComponent() = default;
	SkyboxComponent(const SkyboxComponent&) = default;
	SkyboxComponent(const Ref<Firebox::Skybox>& skybox)
		: Skybox(skybox)
	{
	}
};

struct PostProcessComponent
{
	float Gamma = 1.5;

	PostProcessComponent() = default;
	PostProcessComponent(const PostProcessComponent&) = default;
	PostProcessComponent(float gamma) : Gamma(gamma) {};
};