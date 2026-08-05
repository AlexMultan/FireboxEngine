#pragma once

#include "Rendering/RHI/RendererAPI.h"
#include "Rendering/Materials/Shader.h"
#include "Rendering/Materials/Material.h"
#include "Rendering/Geometry/Mesh.h"
#include "Rendering/Geometry/Grid.h"
#include "Rendering/Skybox/Skybox.h"
#include "Rendering/Targets/ShadowMap.h"
#include "Components/Components.h"
#include "Components/LightComponents.h"
#include "Rendering/Camera/Camera.h"
#include "Rendering/Buffers/UniformBuffer.h"
#include "Rendering/Targets/Framebuffer.h"
#include "Animation/Animator.h"

namespace Firebox {

	enum ViewMode
	{
		Lit = 0,
		Unlit = 1,
		Depth = 2,
		Shadow = 3
	};

	struct PostProcessSettings
	{
		float Gamma = 1.5f;
	};

	class FIREBOX_API Renderer3D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera& camera);
		static void BeginScene(const Camera& camera, const DirectionalLightComponent& directionalLight);
		static void EndScene();

		static void DrawMesh(const Ref<Mesh>& mesh, const Ref<Material>& material, const TransformComponent& transform);
		static void DrawMesh(const Ref<Mesh>& mesh, const Ref<Material>& material, const TransformComponent& transform, const Ref<Animator> animator);
		static void DrawGrid();
		static void DrawSkybox(const Ref<Skybox>& skybox);
		static void SetDirectionalLight(const DirectionalLightComponent& directionalLight);
		static void SetPostProcessSettings(const PostProcessComponent& postProcess);

		static Ref<Shader> GetLitShader();
		static Ref<Shader> GetDepthShader();
		static Ref<Shader> GetShadowShader();
		static Ref<Shader> GetLightShader();
		static Ref<Shader> GetGridShader();
		static const Ref<Framebuffer>& GetMainFramebuffer();
 		static const Ref<Material>& GetDefaultMaterial();
		static void SetGridSize(const float& gridSize);
		static void SetActiveViewMode(const ViewMode& viewMode);

	private:
		static void Flush();
		static void RenderShadowPass();

		struct RenderCommand
		{
			Ref<VertexArray> VAO;
			Ref<Material> Material;
			Mat4 Transform;
			Mat4 InverseNormal;
			Ref<Animator> Animator;
		};

		struct Renderer3DData
		{
			Scope<RendererAPI> RendererAPI;
			DynamicArray<RenderCommand> RenderQueue;
			Ref<Shader> LitShader;
			Ref<Shader> UnlitShader;
			Ref<Shader> DepthShader;
			Ref<Shader> ShadowDepthShader;
			Ref<Shader> LightShader;
			Ref<Shader> GridShader;
			Ref<Material> DefaultMaterial;
			Mat4 ViewProjectionMatrix;
			Mat4 ViewMatrix;
			Mat4 ProjectionMatrix;
			Mat4 LightSpaceMatrix;
			Vector3 CameraPosition;
			float FarPlane;
			float NearPlane;
			float FOV;
			float AspectRatio;
			DirectionalLightComponent DirectionalLight{ {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} };
			Ref<ShadowMap> ShadowMap;
			Ref<Framebuffer> MainFramebuffer;
			Ref<Skybox> ActiveSkybox = nullptr;
			PostProcessSettings PostProcessing{};
		};

		static Renderer3DData s_Data;
		static ViewMode s_ViewMode;

		static Ref<Grid> s_Grid;
		static float s_GridSize;

		static Ref<UniformBuffer> s_ShadowUniformBuffer;
	};
}