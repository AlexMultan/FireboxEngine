#pragma once

#include "Rendering/RHI/RendererAPI.h"
#include "Rendering/Materials/Shader.h"
#include "Rendering/Materials/Material.h"
#include "Rendering/Geometry/Grid.h"
#include "Rendering/Skybox/Skybox.h"
#include "Rendering/Targets/ShadowMap.h"
#include "Rendering/Buffers/UniformBuffer.h"
#include "Rendering/Targets/Framebuffer.h"
#include "Components/LightComponents.h"
#include "Components/CoreComponents.h"
#include "Rendering/Camera/Camera.h"
#include "Buffers/GBuffer.h"
#include "Targets/ShadowMask.h"
#include "PostProcess/SSAO.h"
#include "Animation/Animator.h"
#include "Rendering/Geometry/Quad.h"

class Mesh;
class PostProcessComponent;

namespace Firebox {

	enum ViewMode
	{
		Lit = 0,
		Depth = 1,
		Albedo = 2,
		Normal = 3,
		Position = 4,
		Roughness = 5,
		Metallic = 6,
		AmbientOcclusion = 7,
		DebugCascadeLevels = 8
	};

	class FIREBOX_API Renderer3D
	{
	public:
		// Renderer lifetime
		static void Init();
		static void Shutdown();

		// Frame / scene lifecycle
		static void BeginScene(const Camera& camera);
		static void BeginScene(const Camera& camera, const DirectionalLightComponent& directionalLight);
		static void EndScene();

		// Submission
		static void SubmitMesh(const Ref<Mesh>& mesh, const Ref<Material>& material, const TransformComponent& transform);
		static void SubmitMesh(const Ref<Mesh>& mesh, const Ref<Material>& material, const TransformComponent& transform, const Ref<Animator> animator);
		static void DrawGrid();
		static void DrawSkybox(const Ref<Skybox>& skybox);
		static void SubmitDebugBox(const TransformComponent& transform);

		// Scene state
		static DirectionalLightComponent& GetDirectionalLight();
		static void SetDirectionalLight(const DirectionalLightComponent& directionalLight);
		static PostProcessComponent& GetPostProcessSettings();
		static std::vector<PointLightComponent>& GetPointLights();
		static std::vector<SpotLightComponent>& GetSpotLights();
		static void SetGridSize(const float& gridSize);
		static void SetActiveViewMode(const ViewMode& viewMode);
		static void SetPostProcessComponent(const PostProcessComponent& postProcess);
		static void DestroyPointLight(const PointLightComponent& pointLight);

		// Shader / resource access
		static Ref<Shader> GetLitShader();
		static Ref<Shader> GetGBufferShader();
		static Ref<Shader> GetShadowMaskShader();
		static Ref<Shader> GetAlbedoVisShader();
		static Ref<Shader> GetNormalVisShader();
		static Ref<Shader> GetPositionVisShader();
		static Ref<Shader> GetRoughnessVisShader();
		static Ref<Shader> GetMetallicVisShader();
		static Ref<Shader> GetAmbientOcclusionVisShader();
		static Ref<Shader> GetSSAOShader();
		static Ref<Shader> GetSSAOBlurShader();
		static Ref<Shader> GetDepthShader();
		static Ref<Shader> GetShadowShader();
		static Ref<Shader> GetDebugCascadeLevelsShader();
		static Ref<Shader> GetLightShader();
		static Ref<Shader> GetGridShader();
		static const Ref<Framebuffer>& GetMainFramebuffer();
		static const Ref<Material>& GetDefaultMaterial();
		static const Ref<GBuffer>& GetGBuffer();
		static const Ref<ShadowMask>& GetShadowMask();

		// Events
		static void OnViewportResize(uint width, uint height);

	private:
		struct RenderCommand
		{
			Ref<VertexArray> VAO;
			Ref<Material> Material;
			Mat4x4 Transform;
			Mat4x4 InverseNormal;
			Ref<Animator> Animator;
		};

		static void Flush();
		static void GeometryPass();
		static void SSAOPass();
		static void ShadowMaskPass();
		static void ShadowMapPass();
		static void SkyboxPass();
		static void DebugShapesPass();

		static Ref<Shader> BindLitUniforms();
		static Ref<Shader> BindDepthUniforms();
		static Ref<Shader> BindDebugCascadeUniforms();
		static void SetCascadeUniforms(const Ref<Shader>& shader);
		static void SetSkeletalAnimationUniforms(const Ref<Shader>& shader, const RenderCommand& cmd, Ref<Animator>& lastBoundAnimator);
		static void SetPointLightUniforms(const Ref<Shader>& shader, int count);
		static void SetSpotLightUniforms(const Ref<Shader>& shader, int count);


		struct Renderer3DData
		{
			Scope<RendererAPI> RendererAPI;
			std::vector<RenderCommand> RenderQueue;
			std::vector<Mat4x4> DebugShapesQueue;
			Ref<Shader> LitShader;
			Ref<Shader> GBufferShader;
			Ref<Shader> ShadowMaskShader;
			Ref<Shader> AlbedoVisShader;
			Ref<Shader> NormalVisShader;
			Ref<Shader> PositionVisShader;
			Ref<Shader> RoughnessVisShader;
			Ref<Shader> MetallicVisShader;
			Ref<Shader> AmbientOcclusionVisShader;
			Ref<Shader> SSAOShader;
			Ref<Shader> SSAOBlurShader;
			Ref<Shader> DepthShader;
			Ref<Shader> ShadowDepthShader;
			Ref<Shader> DebugCascadeLevelsShader;
			Ref<Shader> LightShader;
			Ref<Shader> GridShader;
			Ref<Shader> DebugShapeShader;
			Ref<Material> DefaultMaterial;
			Mat4x4 ViewProjectionMatrix;
			Mat4x4 ViewMatrix;
			Mat4x4 ProjectionMatrix;
			Mat4x4 LightSpaceMatrix;
			Vector3 CameraPosition;
			float FarPlane;
			float NearPlane;
			float FOV;
			float AspectRatio;
			DirectionalLightComponent DirectionalLight{ {-0.2f, -1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, 1.0f };
			std::vector<PointLightComponent> PointLights;
			std::vector<SpotLightComponent> SpotLights;
			SpotLightComponent SpotLight;
			Ref<ShadowMap> ShadowMap;
			Ref<Framebuffer> MainFramebuffer;
			Ref<Skybox> ActiveSkybox = nullptr;
			PostProcessComponent PostProcessing;
			Ref<GBuffer> gBuffer;
			Ref<ShadowMask> ShadowMask;
			Ref<SSAO> SSAO;
			Ref<Mesh> BoxMesh;
		};

		static Renderer3DData s_Data;
		static ViewMode s_ViewMode;

		static Ref<Grid> s_Grid;
		static float s_GridSize;

		static Ref<UniformBuffer> s_ShadowUniformBuffer;

		static constexpr int k_MaxPointLights = 32;
		static constexpr int k_MaxSpotLights = 32;
		static constexpr int k_MaxBoneMatrices = 100;
		static constexpr uint32_t k_ShadowMapResolution = 4096;
		static constexpr uint32_t k_DefaultFramebufferWidth = 800;
		static constexpr uint32_t k_DefaultFramebufferHeight = 600;

		static Scope<Quad> s_ScreenQuad;
	};
}