#pragma once

#include "Engine/Rendering/RendererAPI.h"
#include "Engine/Rendering/Resources/Shader.h"
#include "Engine/Rendering/Resources/Material.h"
#include "Engine/Rendering/Resources/Mesh.h"
#include "Engine/Rendering/Resources/Grid.h"
#include "Engine/Components/Components.h"
#include "Engine/Components/LightComponents.h"
#include "Engine/Rendering/Camera/Camera.h"

namespace Firebox {

	class FIREBOX_API Renderer3D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera& camera, const DirectionalLightComponent& directionalLight);
		static void EndScene();

		static void DrawMesh(const Ref<Mesh>& mesh, const Ref<Material>& material, const TransformComponent& transform);
		static void DrawGrid();

		static Ref<Shader> GetBaseShader();
		static Ref<Shader> GetLightShader();
		static Ref<Shader> GetGridShader();
		static const Ref<Material>& GetDefaultMaterial();
		static void SetGridSize(const float& gridSize);

	private:
		static void Flush();

		struct RenderCommand
		{
			Ref<VertexArray> VAO;
			Ref<Material> Material;
			Mat4 Transform;
			Mat4 InverseNormal;
		};

		struct Renderer3DData
		{
			Scope<RendererAPI> RendererAPI;
			std::vector<RenderCommand> RenderQueue;
			Ref<Shader> BaseShader;
			Ref<Shader> LightShader;
			Ref<Shader> GridShader;
			Ref<Material> DefaultMaterial;
			Mat4 ViewProjectionMatrix;
			Vector3 CameraPosition;
			DirectionalLightComponent DirectionalLight;
		};

		static Renderer3DData s_Data;

		static Ref<Grid> s_Grid;
		static float s_GridSize;
	};
}