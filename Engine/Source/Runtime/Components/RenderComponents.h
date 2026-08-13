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
	// Color Grading
	float Gamma = 1.5f;
	float Contrast = 1.0f;
	float Saturation = 1.0f;
	float Gain = 1.0f;
	float Temperature = 6500.0f;
	float Tint = 0.0f;

	// Lens
	float BloomIntensity = 0.75f;
	float Exposure = 1.0f;
	float VignetterIntensity = 0.4f;
	float Sharpen = 0.0f;
	float ChromaticAbberrationIntensity = 0.0f;

	// Film
	float Slope = 0.9f;
	float Toe = 0.5f;

	// Rendering Features
	float AmbientOcculusionIntensity = 0.5f;
	float AmbientOcculusionRadius = 200.0f;
	float MotionBlurIntensity = 0.5f;

	bool InfiniteExtent = true;

	PostProcessComponent() = default;
	PostProcessComponent(const PostProcessComponent&) = default;
	PostProcessComponent(float gamma) : Gamma(gamma) {};
};