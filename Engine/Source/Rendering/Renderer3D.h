#pragma once

#include "Rendering/RendererAPI.h"
#include "Rendering/Resources/Shader.h"
#include "Rendering/Resources/Material.h"
#include "Rendering/Resources/Mesh.h"
#include "Rendering/Resources/Grid.h"
#include "Rendering/Resources/Skybox.h"
#include "Rendering/Resources/ShadowMap.h"
#include "Components/Components.h"
#include "Components/LightComponents.h"
#include "Rendering/Camera/Camera.h"
#include "Rendering/Resources/UniformBuffer.h"
#include "Rendering/Resources/Framebuffer.h"

namespace Firebox {

	enum ViewMode
	{
		Lit = 0,
		Unlit = 1,
		Depth = 2,
		Shadow = 3
	};

	class FIREBOX_API Renderer3D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera& camera, const DirectionalLightComponent& directionalLight);
		static void EndScene();

		static void DrawMesh(const Ref<Mesh>& mesh, const Ref<Material>& material, const TransformComponent& transform);
		static void DrawGrid();
		static void DrawSkybox();

		static Ref<Shader> GetDefaultShader();
		static Ref<Shader> GetDepthShader();
		static Ref<Shader> GetShadowShader();
		static Ref<Shader> GetLightShader();
		static Ref<Shader> GetGridShader();
		static Ref<Shader> GetSkyboxShader();
		static const Ref<Framebuffer>& GetMainFramebuffer();
 		static const Ref<Material>& GetDefaultMaterial();
		static const Ref<Material>& GetSkyboxMaterial();
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
		};

		struct Renderer3DData
		{
			Scope<RendererAPI> RendererAPI;
			DynamicArray<RenderCommand> RenderQueue;
			Ref<Shader> DefaultShader;
			Ref<Shader> UnlitShader;
			Ref<Shader> DepthShader;
			Ref<Shader> ShadowDepthShader;
			Ref<Shader> LightShader;
			Ref<Shader> GridShader;
			Ref<Shader> SkyboxShader;
			Ref<Material> DefaultMaterial;
			Ref<Material> SkyboxMaterial;
			Mat4 ViewProjectionMatrix;
			Mat4 ViewMatrix;
			Mat4 ProjectionMatrix;
			Mat4 LightSpaceMatrix;
			Vector3 CameraPosition;
			float FarPlane;
			float NearPlane;
			float FOV;
			float AspectRatio;
			DirectionalLightComponent DirectionalLight;
			Ref<ShadowMap> ShadowMap;
			Ref<Framebuffer> MainFramebuffer;
		};

		static Renderer3DData s_Data;
		static ViewMode s_ViewMode;

		static Ref<Grid> s_Grid;
		static float s_GridSize;

		static Ref<Skybox> s_Skybox;

		static Ref<UniformBuffer> s_ShadowUniformBuffer;
	};
}