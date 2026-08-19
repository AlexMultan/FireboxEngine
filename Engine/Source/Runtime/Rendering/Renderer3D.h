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

	struct PostProcessingSettings
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
		float VignetteIntensity = 0.4f;
		float Sharpen = 0.0f;
		float ChromaticAbberrationIntensity = 0.0f;

		// Film
		float Slope = 0.9f;
		float Toe = 0.5f;

		// Rendering Features
		int AmbientOcclusionKernelSize = 64;
		float AmbientOcclusionIntensity = 0.5f;
		float AmbientOcclusionRadius = 0.5f;
		float AmbientOcclusionBias = 0.025f;
		bool EnableSSAO = true;
		float MotionBlurIntensity = 0.5f;

		bool InfiniteExtent = true;
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
		static void DrawMesh(const Ref<Mesh>& mesh, const Ref<Material>& material, const TransformComponent& transform);
		static void DrawMesh(const Ref<Mesh>& mesh, const Ref<Material>& material, const TransformComponent& transform, const Ref<Animator> animator);
		static void DrawGrid();
		static void DrawSkybox(const Ref<Skybox>& skybox);

		// Scene state
		static void SetDirectionalLight(const DirectionalLightComponent& directionalLight);
		static void SetPostProcessSettings(const PostProcessComponent& postProcess);
		static std::vector<PointLightComponent>& GetPointLights();
		static std::vector<SpotLightComponent>& GetSpotLights();
		static void SetGridSize(const float& gridSize);
		static void SetActiveViewMode(const ViewMode& viewMode);

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
			Mat4 Transform;
			Mat4 InverseNormal;
			Ref<Animator> Animator;
		};

		static void Flush();
		static void GeometryPass();
		static void SSAOPass();
		static void ShadowMaskPass();
		static void ShadowMapPass();
		static void RenderSkybox();

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
			std::vector<PointLightComponent> PointLights;
			std::vector<SpotLightComponent> SpotLights;
			SpotLightComponent SpotLight;
			Ref<ShadowMap> ShadowMap;
			Ref<Framebuffer> MainFramebuffer;
			Ref<Skybox> ActiveSkybox = nullptr;
			PostProcessingSettings PostProcessing{};
			Ref<GBuffer> gBuffer;
			Ref<ShadowMask> ShadowMask;
			Ref<SSAO> SSAO;
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