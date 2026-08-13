#include "Renderer3D.h"
#include "Core/Log.h"
#include "Editor/EnginePaths.h"
#include "Utils/Assert.h"
#include "Components/RenderComponents.h"
#include "Geometry/PrimitiveShapes.h"

#include <algorithm>
#include <cfloat>
#include <limits>

Firebox::Renderer3D::Renderer3DData Firebox::Renderer3D::s_Data;
Firebox::ViewMode Firebox::Renderer3D::s_ViewMode = Firebox::ViewMode::Lit;
Ref<Firebox::Grid> Firebox::Renderer3D::s_Grid = nullptr;
Ref<Firebox::UniformBuffer> Firebox::Renderer3D::s_ShadowUniformBuffer = nullptr;
float Firebox::Renderer3D::s_GridSize = 10.0f;
Scope<Firebox::Quad> Firebox::Renderer3D::s_ViewportQuad = nullptr;

const Ref<Firebox::Framebuffer>& Firebox::Renderer3D::GetMainFramebuffer() { return s_Data.MainFramebuffer; }
const Ref<Firebox::Material>& Firebox::Renderer3D::GetDefaultMaterial() { return s_Data.DefaultMaterial; }
const Ref<Firebox::GBuffer>& Firebox::Renderer3D::GetGBuffer() { return s_Data.gBuffer; }
const Ref<Firebox::ShadowMask>& Firebox::Renderer3D::GetShadowMask() { return s_Data.ShadowMask; }

Ref<Firebox::Shader> Firebox::Renderer3D::GetLitShader() { return s_Data.LitShader; }
Ref<Firebox::Shader> Firebox::Renderer3D::GetGBufferShader() { return s_Data.GBufferShader; }
Ref<Firebox::Shader> Firebox::Renderer3D::GetShadowMaskShader() { return s_Data.ShadowMaskShader; }
Ref<Firebox::Shader> Firebox::Renderer3D::GetUnlitShader() { return s_Data.UnlitShader; }
Ref<Firebox::Shader> Firebox::Renderer3D::GetDepthShader() { return s_Data.DepthShader; }
Ref<Firebox::Shader> Firebox::Renderer3D::GetShadowShader() { return s_Data.ShadowDepthShader; }
Ref<Firebox::Shader> Firebox::Renderer3D::GetDebugCascadeLevelsShader() { return s_Data.DebugCascadeLevelsShader; }
Ref<Firebox::Shader> Firebox::Renderer3D::GetLightShader() { return s_Data.LightShader; }
Ref<Firebox::Shader> Firebox::Renderer3D::GetGridShader() { return s_Data.GridShader; }

void Firebox::Renderer3D::SetGridSize(const float& gridSize) { s_GridSize = gridSize; }
void Firebox::Renderer3D::SetActiveViewMode(const ViewMode& viewMode) { s_ViewMode = viewMode; }


void Firebox::Renderer3D::Init()
{
	FB_CORE_TRACE("Renderer3D::Init()");
	FB_CORE_TRACE("Renderer3D::Init start");

	s_Data.RendererAPI = RendererAPI::Create();
	FB_ASSERT(s_Data.RendererAPI, "RendererAPI is null!");
	s_Data.RendererAPI->Init();

	FB_CORE_TRACE("Creating LitShader...");
	s_Data.LitShader = Shader::Create(Firebox::EngineContent::Get("Shaders/GLSL/Lit.vert").string().c_str(),
		Firebox::EngineContent::Get("Shaders/GLSL/Lit.frag").string().c_str(), nullptr);

	FB_CORE_TRACE("Creating GBufferShader...");
	s_Data.GBufferShader = Shader::Create(Firebox::EngineContent::Get("Shaders/GLSL/GBuffer.vert").string().c_str(),
		Firebox::EngineContent::Get("Shaders/GLSL/GBuffer.frag").string().c_str(), nullptr);

	FB_CORE_TRACE("Creating ShadowMaskShader...");
	s_Data.ShadowMaskShader = Shader::Create(Firebox::EngineContent::Get("Shaders/GLSL/ShadowMask.vert").string().c_str(),
		Firebox::EngineContent::Get("Shaders/GLSL/ShadowMask.frag").string().c_str(), nullptr);

	FB_CORE_TRACE("Creating UnlitShader...");
	s_Data.UnlitShader = Shader::Create(Firebox::EngineContent::Get("Shaders/GLSL/Unlit.vert").string().c_str(),
		Firebox::EngineContent::Get("Shaders/GLSL/Unlit.frag").string().c_str(), nullptr);

	FB_CORE_TRACE("Creating DepthShader...");
	s_Data.DepthShader = Shader::Create(Firebox::EngineContent::Get("Shaders/GLSL/DepthVis.vert").string().c_str(),
		Firebox::EngineContent::Get("Shaders/GLSL/DepthVis.frag").string().c_str(), nullptr);

	FB_CORE_TRACE("Creating ShadowMapShader...");
	s_Data.ShadowDepthShader = Shader::Create(Firebox::EngineContent::Get("Shaders/GLSL/ShadowMap.vert").string().c_str(),
		Firebox::EngineContent::Get("Shaders/GLSL/ShadowMap.frag").string().c_str(),
		Firebox::EngineContent::Get("Shaders/GLSL/ShadowMap.geom").string().c_str());
	s_Data.ShadowMap = Firebox::ShadowMap::Create(k_ShadowMapResolution);

	s_ShadowUniformBuffer = Firebox::UniformBuffer::Create();

	s_Data.DebugCascadeLevelsShader = Shader::Create(Firebox::EngineContent::Get("Shaders/GLSL/DebugCascadeLevels.vert").string().c_str(),
		Firebox::EngineContent::Get("Shaders/GLSL/DebugCascadeLevels.frag").string().c_str(), nullptr);

	s_Data.LightShader = Shader::Create(Firebox::EngineContent::Get("Shaders/GLSL/Light.vert").string().c_str(),
		Firebox::EngineContent::Get("Shaders/GLSL/Light.frag").string().c_str(), nullptr);
	s_Data.GridShader = Shader::Create(Firebox::EngineContent::Get("Shaders/GLSL/Grid.vert").string().c_str(),
		Firebox::EngineContent::Get("Shaders/GLSL/Grid.frag").string().c_str(), nullptr);

	s_Data.DefaultMaterial = CreateRef<Material>(s_Data.LitShader);
	s_Data.DefaultMaterial->SetDiffuseTexture(Firebox::Texture::Create(Firebox::EngineContent::Get("Textures/T_Default.png").string()));
	s_Data.DefaultMaterial->SetSpecularTexture(Firebox::Texture::Create(Firebox::EngineContent::Get("Textures/T_Default.png").string()));
	s_Data.DefaultMaterial->SetNormalTexture(Firebox::Texture::Create(Firebox::EngineContent::Get("Textures/T_Default.png").string()));

	s_Data.MainFramebuffer = Firebox::Framebuffer::Create({ k_DefaultFramebufferWidth, k_DefaultFramebufferHeight });
	s_Data.gBuffer = Firebox::GBuffer::Create();
	s_Data.gBuffer->ResizeGBuffer(s_Data.MainFramebuffer->GetSpecs().Width, s_Data.MainFramebuffer->GetSpecs().Height);
	s_Data.ShadowMask = Firebox::ShadowMask::Create();
	s_Data.ShadowMask->ResizeShadowMask(s_Data.MainFramebuffer->GetSpecs().Width, s_Data.MainFramebuffer->GetSpecs().Height);

	s_ViewportQuad = CreateScope<Firebox::Quad>();

	FB_ASSERT(s_Data.LitShader, "DefaultShader is null after creation!");
	s_Grid = CreateRef<Firebox::Grid>();

	s_Data.ShadowMaskShader->UseShader();
	s_Data.ShadowMaskShader->SetInt("u_gPosition", 27);
	s_Data.ShadowMaskShader->SetInt("u_gNormal", 28);

	s_Data.LitShader->UseShader();
	s_Data.LitShader->SetInt("u_gPosition", 27);
	s_Data.LitShader->SetInt("u_gNormal", 28);
	s_Data.LitShader->SetInt("u_gAlbedoSpec", 29);
	s_Data.LitShader->SetInt("u_ShadowMask", 30);

	s_Data.DebugCascadeLevelsShader->UseShader();
	s_Data.DebugCascadeLevelsShader->SetInt("u_gPosition", 27);
}

void Firebox::Renderer3D::Shutdown()
{
	s_Data.RenderQueue.clear();
}

void Firebox::Renderer3D::BeginScene(const Camera& camera)
{
	BeginScene(camera, s_Data.DirectionalLight);
}

void Firebox::Renderer3D::BeginScene(const Camera& camera, const DirectionalLightComponent& directionalLight)
{
	s_Data.RendererAPI->ClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	s_Data.RendererAPI->Clear(APIEnum::API_COLOR_BUFFER_BIT | APIEnum::API_DEPTH_BUFFER_BIT | APIEnum::API_STENCIL_BUFFER_BIT);

	s_Data.CameraPosition = camera.GetPosition();
	s_Data.NearPlane = camera.GetNearPlane();
	s_Data.FarPlane = camera.GetFarPlane();
	s_Data.FOV = camera.GetFOV();
	s_Data.AspectRatio = camera.GetAspectRatio();
	s_Data.ViewMatrix = camera.GetViewMatrix();
	s_Data.ProjectionMatrix = camera.GetPerspective();
	s_Data.ViewProjectionMatrix = s_Data.ProjectionMatrix * s_Data.ViewMatrix;
	s_Data.DirectionalLight = directionalLight;

	s_Data.ShadowMap->SetShadowMapProps(s_Data.FOV, s_Data.NearPlane, s_Data.FarPlane, s_Data.AspectRatio, s_Data.ViewMatrix,
		s_Data.DirectionalLight.Direction);
	s_Data.ShadowMap->SetCascadeLevels();

	s_Data.RenderQueue.clear();
}

void Firebox::Renderer3D::EndScene()
{
	std::sort(s_Data.RenderQueue.begin(), s_Data.RenderQueue.end(), [](const RenderCommand& a, const RenderCommand& b)
		{
			return a.Material->GetShader()->GetID() < b.Material->GetShader()->GetID();
		});

	ShadowMapPass();
	s_Data.MainFramebuffer->BindFramebuffer();
	GeometryPass();
	ShadowMaskPass();
	RenderSkybox();
	DrawGrid();
	Flush();
	s_Data.MainFramebuffer->UnbindFramebuffer();
}

void Firebox::Renderer3D::DrawMesh(const Ref<Mesh>& mesh, const Ref<Material>& material, const TransformComponent& transform)
{
	s_Data.RenderQueue.push_back({ mesh->GetVertexArray(), material, transform.GetTransform(), transform.GetInverseNormal(), nullptr });
}

void Firebox::Renderer3D::DrawMesh(const Ref<Mesh>& mesh, const Ref<Material>& material, const TransformComponent& transform, const Ref<Animator> animator)
{
	s_Data.RenderQueue.push_back({ mesh->GetVertexArray(), material, transform.GetTransform(), transform.GetInverseNormal(), animator });
}

void Firebox::Renderer3D::DrawGrid()
{
	s_Data.RendererAPI->Enable(APIEnum::API_BLEND);
	s_Data.RendererAPI->SetDepthFunc(Firebox::APIEnum::API_GEQUAL);

	s_Data.GridShader->UseShader();
	s_Data.GridShader->SetMat4("u_ViewProjection", s_Data.ViewProjectionMatrix);
	s_Data.GridShader->SetMat4("u_Model", Mat4(1.0f));
	s_Data.GridShader->SetVector3("u_CamPos", s_Data.CameraPosition);
	s_Data.GridShader->SetFloat("u_CellSize", s_GridSize);

	FB_ASSERT(s_Grid, "Grid is null, was Renderer3D::Init() called?");
	s_Data.RendererAPI->DrawIndexed(s_Grid->GetVertexArray());

	s_Data.RendererAPI->SetDepthFunc(Firebox::APIEnum::API_GREATER);
	s_Data.RendererAPI->Disable(APIEnum::API_BLEND);

}

void Firebox::Renderer3D::DrawSkybox(const Ref<Skybox>& skybox)
{
	FB_ASSERT(skybox, "Attempted to set a null skybox");
	s_Data.ActiveSkybox = skybox;
}

void Firebox::Renderer3D::SetDirectionalLight(const DirectionalLightComponent& directionalLight)
{
	s_Data.DirectionalLight = directionalLight;
}

void Firebox::Renderer3D::SetPostProcessSettings(const PostProcessComponent& postProcess)
{
	s_Data.PostProcessing.Gamma = postProcess.Gamma;
	s_Data.PostProcessing.Contrast = postProcess.Contrast;
	s_Data.PostProcessing.Saturation = postProcess.Saturation;
	s_Data.PostProcessing.Gain = postProcess.Gain;
	s_Data.PostProcessing.Temperature = postProcess.Temperature;
	s_Data.PostProcessing.Tint = postProcess.Tint;
	s_Data.PostProcessing.BloomIntensity = postProcess.BloomIntensity;
	s_Data.PostProcessing.Exposure = postProcess.Exposure;
	s_Data.PostProcessing.VignetteIntensity = postProcess.VignetterIntensity;
	s_Data.PostProcessing.Sharpen = postProcess.Sharpen;
	s_Data.PostProcessing.ChromaticAberrationIntensity = postProcess.ChromaticAbberrationIntensity;
	s_Data.PostProcessing.Slope = postProcess.Slope;
	s_Data.PostProcessing.Toe = postProcess.Toe;
	s_Data.PostProcessing.AmbientOcclusionIntensity = postProcess.AmbientOcculusionIntensity;
	s_Data.PostProcessing.AmbientOcclusionRadius = postProcess.AmbientOcculusionRadius;
	s_Data.PostProcessing.MotionBlurIntensity = postProcess.MotionBlurIntensity;
	s_Data.PostProcessing.InfiniteExtent = postProcess.InfiniteExtent;
}

std::vector<PointLightComponent>& Firebox::Renderer3D::GetPointLights()
{
	return s_Data.PointLights;
}

std::vector<SpotLightComponent>& Firebox::Renderer3D::GetSpotLights()
{
	return s_Data.SpotLights;
}

void Firebox::Renderer3D::SetCascadeUniforms(const Ref<Shader>& shader)
{
	const auto& cascadeLevels = s_Data.ShadowMap->GetCascadeLevels();
	shader->SetInt("u_CascadeCount", static_cast<int>(cascadeLevels.size()));
	for (size_t i = 0; i < cascadeLevels.size(); i++)
		shader->SetFloat("u_CascadePlaneDistances[" + std::to_string(i) + "]", cascadeLevels[i]);
}

void Firebox::Renderer3D::SetSkeletalAnimationUniforms(const Ref<Shader>& shader, const RenderCommand& cmd, Ref<Animator>& lastBoundAnimator)
{
	if (cmd.Animator)
	{
		if (cmd.Animator != lastBoundAnimator)
		{
			const auto& transforms = cmd.Animator->GetFinalBoneMatrices();
			for (size_t i = 0; i < transforms.size(); i++)
				shader->SetMat4("u_FinalBoneMatrices[" + std::to_string(i) + "]", transforms[i]);
			lastBoundAnimator = cmd.Animator;
		}
	}
	else
	{
		lastBoundAnimator = nullptr;
		for (int i = 0; i < k_MaxBoneMatrices; i++)
			shader->SetMat4("u_FinalBoneMatrices[" + std::to_string(i) + "]", Mat4(1.0f));
	}
}

void Firebox::Renderer3D::SetPointLightUniforms(const Ref<Shader>& shader, int count)
{
	if (count <= 0)
		return;

	shader->SetInt("u_NumberOfPointLights", count);
	for (int i = 0; i < count; i++)
	{
		const auto& light = s_Data.PointLights[i];
		const std::string prefix = "u_PointLights[" + std::to_string(i) + "].";
		shader->SetVector3(prefix + "position", light.Position);
		shader->SetVector3(prefix + "ambient", light.Color * 0.2f);
		shader->SetVector3(prefix + "diffuse", light.Color);
		shader->SetVector3(prefix + "specular", light.Color);
		shader->SetFloat(prefix + "constant", light.Constant);
		shader->SetFloat(prefix + "linear", light.Linear);
		shader->SetFloat(prefix + "quadratic", light.Quadratic);
	}
}

void Firebox::Renderer3D::SetSpotLightUniforms(const Ref<Shader>& shader, int count)
{
	if (count <= 0)
		return;

	shader->SetInt("u_NumberOfSpotLights", count);
	for (int i = 0; i < count; i++)
	{
		const auto& light = s_Data.SpotLights[i];
		const std::string prefix = "u_SpotLights[" + std::to_string(i) + "].";
		shader->SetVector3(prefix + "position", light.Position);
		shader->SetVector3(prefix + "direction", light.Direction);
		shader->SetVector3(prefix + "ambient", light.Color * 0.2f);
		shader->SetVector3(prefix + "diffuse", light.Color);
		shader->SetVector3(prefix + "specular", light.Color);
		shader->SetFloat(prefix + "constant", light.Constant);
		shader->SetFloat(prefix + "linear", light.Linear);
		shader->SetFloat(prefix + "quadratic", light.Quadratic);
		shader->SetFloat(prefix + "cutOff", light.CutOff);
		shader->SetFloat(prefix + "outerCutOff", light.OuterCutOff);
	}
}

Ref<Firebox::Shader> Firebox::Renderer3D::BindLitUniforms()
{
	Ref<Shader> shader = s_Data.LitShader;
	shader->UseShader();
	shader->SetVector3("u_ViewPos", s_Data.CameraPosition);
	shader->SetFloat("u_PostProcessSettings.gamma", s_Data.PostProcessing.Gamma);

	shader->SetVector3("u_DirectionalLight.direction", s_Data.DirectionalLight.Direction);
	shader->SetVector3("u_DirectionalLight.ambient", s_Data.DirectionalLight.Color * 0.2f);
	shader->SetVector3("u_DirectionalLight.diffuse", s_Data.DirectionalLight.Color);
	shader->SetVector3("u_DirectionalLight.specular", s_Data.DirectionalLight.Color);

	const int numberOfPointLights = std::min(static_cast<int>(s_Data.PointLights.size()), k_MaxPointLights);
	const int numberOfSpotLights = std::min(static_cast<int>(s_Data.SpotLights.size()), k_MaxSpotLights);
	SetPointLightUniforms(shader, numberOfPointLights);
	SetSpotLightUniforms(shader, numberOfSpotLights);

	return shader;
}

Ref<Firebox::Shader> Firebox::Renderer3D::BindUnlitUniforms()
{
	Ref<Shader> shader = s_Data.UnlitShader;
	shader->UseShader();
	return shader;
}


Ref<Firebox::Shader> Firebox::Renderer3D::BindDepthUniforms()
{
	Ref<Shader> shader = s_Data.DepthShader;
	shader->UseShader();
	shader->SetMat4("u_ViewProjection", s_Data.ViewProjectionMatrix);
	shader->SetFloat("u_Near", s_Data.NearPlane);
	shader->SetFloat("u_Far", s_Data.FarPlane);
	return shader;
}

Ref<Firebox::Shader> Firebox::Renderer3D::BindDebugCascadeUniforms()
{
	Ref<Shader> shader = s_Data.DebugCascadeLevelsShader;
	shader->UseShader();
	shader->SetMat4("u_View", s_Data.ViewMatrix);
	SetCascadeUniforms(shader);
	return shader;
}

void Firebox::Renderer3D::Flush()
{
	s_Data.RendererAPI->SetViewport(0, 0, s_Data.MainFramebuffer->GetSpecs().Width, s_Data.MainFramebuffer->GetSpecs().Height);
	s_Data.RendererAPI->Clear(APIEnum::API_COLOR_BUFFER_BIT | APIEnum::API_DEPTH_BUFFER_BIT | APIEnum::API_STENCIL_BUFFER_BIT);

	Ref<Shader> activeShader;

	switch (s_ViewMode)
	{
	case ViewMode::Lit:
		activeShader = BindLitUniforms();
		break;

	case ViewMode::Unlit:
		activeShader = BindUnlitUniforms();
		break;

	case ViewMode::Depth:
		activeShader = BindDepthUniforms();
		break;

	case ViewMode::DebugCascadeLevels:
		activeShader = BindDebugCascadeUniforms();
		break;

	case ViewMode::Shadow:
		break;

	default:
		FB_ASSERT(false, "Unhandled ViewMode in Renderer3D::Flush()");
		break;
	}

	s_Data.RendererAPI->Disable(APIEnum::API_DEPTH_TEST);
	s_Data.RendererAPI->DrawIndexed(s_ViewportQuad->GetVertexArray());
	s_Data.RendererAPI->Enable(APIEnum::API_DEPTH_TEST);

	s_Data.RenderQueue.clear();

	s_Data.gBuffer->ReadGBuffer();
	s_Data.gBuffer->DrawGBuffer(s_Data.MainFramebuffer->GetID());
	s_Data.gBuffer->BlitGBuffer();
}

void Firebox::Renderer3D::GeometryPass()
{
	static Ref<Animator> lastBoundAnimator = nullptr;

	s_Data.RendererAPI->ClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	s_Data.gBuffer->ClearGBuffer();

	s_Data.gBuffer->BindGBuffer();
	s_Data.gBuffer->ClearGBuffer();
	s_Data.RendererAPI->Disable(APIEnum::API_BLEND);
	s_Data.GBufferShader->UseShader();

	for (auto& cmd : s_Data.RenderQueue)
	{
		cmd.Material->BindMaterial(s_Data.GBufferShader);
		s_Data.GBufferShader->SetMat4("u_ViewProjection", s_Data.ViewProjectionMatrix);
		s_Data.GBufferShader->SetMat3("u_InverseNormal", cmd.InverseNormal);
		s_Data.GBufferShader->SetMat4("u_Model", cmd.Transform);
		SetSkeletalAnimationUniforms(s_Data.GBufferShader, cmd, lastBoundAnimator);
		s_Data.RendererAPI->DrawIndexed(cmd.VAO);
	}

	s_Data.gBuffer->UnbindGBuffer();
	s_Data.RendererAPI->Clear(APIEnum::API_COLOR_BUFFER_BIT | APIEnum::API_DEPTH_BUFFER_BIT | APIEnum::API_STENCIL_BUFFER_BIT);
}


// NOTE: Shadow Mask framebuffer and texture is valid, but it remains black at all times. Changing any value in the ShadowMaskShader does not change
// the end result of the final output. It's possible gBuffer textures that are passed into ShadowMaskShader are in the view space instead of world space. 
void Firebox::Renderer3D::ShadowMaskPass()
{
	s_Data.gBuffer->BindGBufferPositionNormal();
	s_Data.ShadowMask->BindShadowMask();
	s_Data.RendererAPI->Clear(APIEnum::API_DEPTH_BUFFER_BIT);
	s_Data.ShadowMaskShader->UseShader();
	s_Data.ShadowMaskShader->SetFloat("u_FarPlane", s_Data.FarPlane);
	s_Data.ShadowMaskShader->SetMat4("u_View", s_Data.ViewMatrix);
	s_Data.ShadowMaskShader->SetVector3("u_LightDirection", s_Data.DirectionalLight.Direction);
	SetCascadeUniforms(s_Data.ShadowMaskShader);
	s_Data.RendererAPI->BindTextureArray(31, s_Data.ShadowMap->GetDepthTexture());
	s_Data.ShadowMaskShader->SetInt("u_ShadowMap", 31);

	s_Data.RendererAPI->Clear(APIEnum::API_COLOR_BUFFER_BIT);

	s_Data.RendererAPI->Disable(APIEnum::API_DEPTH_TEST);
	s_Data.RendererAPI->DrawIndexed(s_ViewportQuad->GetVertexArray());
	s_Data.RendererAPI->Enable(APIEnum::API_DEPTH_TEST);
	
	s_Data.ShadowMask->UnbindShadowMask();
	s_Data.gBuffer->BindGBufferAlbedo();
	s_Data.MainFramebuffer->BindFramebuffer();
}

void Firebox::Renderer3D::RenderSkybox()
{
	if (!s_Data.ActiveSkybox)
		return;

	const Mat4 viewNoTranslation = Mat4(Mat3(s_Data.ViewMatrix));
	const Mat4 skyboxViewProjection = s_Data.ProjectionMatrix * viewNoTranslation;

	s_Data.RendererAPI->SetDepthFunc(Firebox::APIEnum::API_GEQUAL);
	s_Data.ActiveSkybox->GetMaterial()->BindMaterial();
	s_Data.ActiveSkybox->GetShader()->UseShader();
	s_Data.ActiveSkybox->GetShader()->SetMat4("u_ViewProjection", skyboxViewProjection);
	s_Data.RendererAPI->DrawIndexed(s_Data.ActiveSkybox->GetVertexArray());
	s_Data.RendererAPI->SetDepthFunc(Firebox::APIEnum::API_GREATER);

	s_Data.ActiveSkybox = nullptr;
}

void Firebox::Renderer3D::ShadowMapPass()
{
	const auto lightMatrices = s_Data.ShadowMap->GetLightSpaceMatrices();
	s_Data.ShadowMap->BindShadowMap();

	s_Data.RendererAPI->SetDepthFunc(Firebox::APIEnum::API_LESS);
	s_Data.RendererAPI->ClearDepth(1.0f);

	s_ShadowUniformBuffer->BindUniformBuffer();
	for (size_t i = 0; i < lightMatrices.size(); i++)
		s_Data.RendererAPI->BufferSubData(Firebox::APIEnum::API_UNIFORM_BUFFER, i * sizeof(Mat4), sizeof(Mat4), &lightMatrices[i]);
	s_ShadowUniformBuffer->UnbindUniformBuffer();

	s_Data.RendererAPI->CullFace(Firebox::APIEnum::API_BACK);
	s_Data.ShadowDepthShader->UseShader();

	for (auto& cmd : s_Data.RenderQueue)
	{
		s_Data.ShadowDepthShader->SetMat4("u_Model", cmd.Transform);
		s_Data.RendererAPI->DrawIndexed(cmd.VAO);
	}

	s_Data.RendererAPI->CullFace(Firebox::APIEnum::API_FRONT);
	s_Data.ShadowMap->UnbindShadowMap();
	s_Data.RendererAPI->SetDepthFunc(Firebox::APIEnum::API_GREATER);
	s_Data.RendererAPI->ClearDepth(0.0f);
}

void Firebox::Renderer3D::OnViewportResize(uint width, uint height)
{
	if (width == s_Data.MainFramebuffer->GetSpecs().Width && height == s_Data.MainFramebuffer->GetSpecs().Height) return;
	s_Data.MainFramebuffer->ResizeFramebuffer(width, height);
	s_Data.gBuffer->ResizeGBuffer(width, height);
	s_Data.ShadowMask->ResizeShadowMask(width, height);
}