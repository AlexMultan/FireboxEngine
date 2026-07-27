#include "Renderer3D.h"
#include "Core/Log.h"
#include "Editor/EnginePaths.h"
#include "Utils/Assert.h"

#include <algorithm>
#include <cfloat>
#include <limits>

Firebox::Renderer3D::Renderer3DData Firebox::Renderer3D::s_Data;
Firebox::ViewMode Firebox::Renderer3D::s_ViewMode = Firebox::ViewMode::Lit;
Ref<Firebox::Grid> Firebox::Renderer3D::s_Grid = nullptr;
const Ref<Firebox::Framebuffer>& Firebox::Renderer3D::GetMainFramebuffer() { return s_Data.MainFramebuffer; }
Ref<Firebox::UniformBuffer> Firebox::Renderer3D::s_ShadowUniformBuffer = nullptr;
Ref<Firebox::Shader> Firebox::Renderer3D::GetLitShader() { return s_Data.LitShader; }
Ref<Firebox::Shader> Firebox::Renderer3D::GetLightShader() { return s_Data.LightShader; }
Ref<Firebox::Shader> Firebox::Renderer3D::GetGridShader() { return s_Data.GridShader; }
const Ref<Firebox::Material>& Firebox::Renderer3D::GetDefaultMaterial() { return s_Data.DefaultMaterial; }
void Firebox::Renderer3D::SetGridSize(const float& gridSize) { s_GridSize = gridSize; }

void Firebox::Renderer3D::SetActiveViewMode(const ViewMode& viewMode)
{
	s_ViewMode = viewMode;
}

float Firebox::Renderer3D::s_GridSize = 10.0f;

void Firebox::Renderer3D::Init()
{
	FB_CORE_TRACE("Renderer3D::Init() called");
	FB_CORE_TRACE("Renderer3D::Init start");

	s_Data.RendererAPI = RendererAPI::Create();
	FB_ASSERT(s_Data.RendererAPI, "RendererAPI is null!");
	s_Data.RendererAPI->Init();

	FB_CORE_TRACE("Creating DefaultShader...");
	s_Data.LitShader = Shader::Create(Firebox::EngineContent::Get("Shaders/GLSL/Lit.vert").string().c_str(),
		Firebox::EngineContent::Get("Shaders/GLSL/Lit.frag").string().c_str(), nullptr);
	s_Data.UnlitShader = Shader::Create(Firebox::EngineContent::Get("Shaders/GLSL/Unlit.vert").string().c_str(),
		Firebox::EngineContent::Get("Shaders/GLSL/Unlit.frag").string().c_str(), nullptr);
	s_Data.DepthShader = Shader::Create(Firebox::EngineContent::Get("Shaders/GLSL/DepthVis.vert").string().c_str(),
		Firebox::EngineContent::Get("Shaders/GLSL/DepthVis.frag").string().c_str(), nullptr);

	s_Data.MainFramebuffer = Firebox::Framebuffer::Create({ 800, 600 });

	s_Data.ShadowDepthShader = Shader::Create(Firebox::EngineContent::Get("Shaders/GLSL/ShadowMap.vert").string().c_str(),
		Firebox::EngineContent::Get("Shaders/GLSL/ShadowMap.frag").string().c_str(), 
		Firebox::EngineContent::Get("Shaders/GLSL/ShadowMap.geom").string().c_str());
	s_Data.ShadowMap = Firebox::ShadowMap::Create(4096);

	s_ShadowUniformBuffer = Firebox::UniformBuffer::Create();

	s_Data.LightShader = Shader::Create(Firebox::EngineContent::Get("Shaders/GLSL/Light.vert").string().c_str(),
		Firebox::EngineContent::Get("Shaders/GLSL/Light.frag").string().c_str(), nullptr);
	s_Data.GridShader = Shader::Create(Firebox::EngineContent::Get("Shaders/GLSL/Grid.vert").string().c_str(),
		Firebox::EngineContent::Get("Shaders/GLSL/Grid.frag").string().c_str(), nullptr);

	s_Data.DefaultMaterial = CreateRef<Material>(s_Data.LitShader);
	s_Data.DefaultMaterial->SetDiffuseTexture(Firebox::Texture::Create(Firebox::EngineContent::Get("Textures/T_Default.png").string()));
	s_Data.DefaultMaterial->SetSpecularTexture(Firebox::Texture::Create(Firebox::EngineContent::Get("Textures/T_Default.png").string()));
	s_Data.DefaultMaterial->SetNormalTexture(Firebox::Texture::Create(Firebox::EngineContent::Get("Textures/T_Default.png").string()));

	FB_ASSERT(s_Data.LitShader, "DefaultShader is null after creation!");
	s_Grid = CreateRef<Firebox::Grid>();
}

void Firebox::Renderer3D::Shutdown()
{
	s_Data.RenderQueue.clear();
}

void Firebox::Renderer3D::BeginScene(const Camera& camera, const DirectionalLightComponent& directionalLight)
{
	s_Data.RendererAPI->ClearColor(Vector4(0.1f, 0.1f, 0.1f, 1.0f));
	s_Data.RendererAPI->Clear();

	s_Data.CameraPosition = camera.GetPosition();
	s_Data.NearPlane = camera.GetNearPlane();
	s_Data.FarPlane = camera.GetFarPlane();
	s_Data.FOV = camera.GetFOV();
	s_Data.AspectRatio = camera.GetAspectRatio();
	s_Data.ViewProjectionMatrix = camera.GetPerspective() * camera.GetViewMatrix();
	s_Data.ViewMatrix = camera.GetViewMatrix();
	s_Data.ProjectionMatrix = camera.GetPerspective();
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
	RenderShadowPass();
	s_Data.MainFramebuffer->BindFramebuffer();
	Flush();
	DrawGrid();
	s_Data.MainFramebuffer->UnbindFramebuffer();
}

void Firebox::Renderer3D::DrawMesh(const Ref<Mesh>& mesh, const Ref<Material>& material, const TransformComponent& transform)
{
	s_Data.RenderQueue.push_back({ mesh->GetVertexArray(), material, transform.GetTransform(), transform.GetInverseNormal(), nullptr});
}

void Firebox::Renderer3D::DrawMesh(const Ref<Mesh>& mesh, const Ref<Material>& material, const TransformComponent& transform, const Ref<Animator> animator)
{
	s_Data.RenderQueue.push_back({ mesh->GetVertexArray(), material, transform.GetTransform(), transform.GetInverseNormal(), animator });
}

void Firebox::Renderer3D::DrawGrid()
{
	s_Data.GridShader->UseShader();
	s_Data.GridShader->SetMat4("u_ViewProjection", s_Data.ViewProjectionMatrix);
	s_Data.GridShader->SetMat4("u_Model", Mat4(1.0f));
	s_Data.GridShader->SetVector3("u_CamPos", s_Data.CameraPosition);
	s_Data.GridShader->SetFloat("u_CellSize", s_GridSize);

	if (s_Grid) [[likely]]
		s_Data.RendererAPI->DrawIndexed(s_Grid->GetVertexArray());
}

void Firebox::Renderer3D::DrawSkybox(const Ref<Skybox>& skybox)
{
	if (skybox) [[likely]]
	{
		s_Data.ActiveSkybox = skybox;
	}
}

void Firebox::Renderer3D::Flush()
{
	s_Data.RendererAPI->SetViewport(0, 0, s_Data.MainFramebuffer->GetSpecs().Width, s_Data.MainFramebuffer->GetSpecs().Height);
	s_Data.RendererAPI->Clear();
	Ref<Animator> lastBoundAnimator = nullptr;

	for(auto& cmd : s_Data.RenderQueue)
	{
		Ref<Shader> activeShader;

		switch (s_ViewMode)
		{
		case ViewMode::Lit:
			activeShader = s_Data.LitShader;
			activeShader->UseShader();
			activeShader->SetFloat("u_FarPlane", s_Data.FarPlane);
			activeShader->SetInt("u_CascadeCount", s_Data.ShadowMap->GetCascadeLevels().size());
			for (size_t i = 0; i < s_Data.ShadowMap->GetCascadeLevels().size(); i++)
				activeShader->SetFloat("u_CascadePlaneDistances[" + std::to_string(i) + "]", s_Data.ShadowMap->GetCascadeLevels()[i]);
			s_Data.RendererAPI->BindTextureArray(31, s_Data.ShadowMap->GetDepthTexture());
			activeShader->SetInt("u_ShadowMap", 31);

			cmd.Material->BindMaterial();
			activeShader->SetMat4("u_View", s_Data.ViewMatrix);
			activeShader->SetMat4("u_ViewProjection", s_Data.ViewProjectionMatrix);
			activeShader->SetVector3("u_ViewPos", s_Data.CameraPosition);
			activeShader->SetMat3("u_InverseNormal", cmd.InverseNormal);

			if (cmd.Animator)
			{
				if (cmd.Animator != lastBoundAnimator)
				{
					auto transforms = cmd.Animator->GetFinalBoneMatrices();
					for (size_t i = 0; i < transforms.size(); i++)
						activeShader->SetMat4("u_FinalBoneMatrices[" + std::to_string(i) + "]", transforms[i]);
					lastBoundAnimator = cmd.Animator;
				}
			}
			else
			{
				lastBoundAnimator = nullptr;
				for (size_t i = 0; i < 256; i++)
					activeShader->SetMat4("u_FinalBoneMatrices[" + std::to_string(i) + "]", Mat4(1.0f));
			}
			
			activeShader->SetVector3("u_DirectionalLight.direction", s_Data.DirectionalLight.Direction);
			activeShader->SetVector3("u_DirectionalLight.ambient", s_Data.DirectionalLight.Color * 0.2f);
			activeShader->SetVector3("u_DirectionalLight.diffuse", s_Data.DirectionalLight.Color);
			activeShader->SetVector3("u_DirectionalLight.specular", s_Data.DirectionalLight.Color);
			break;

		case ViewMode::Unlit:
			activeShader = s_Data.UnlitShader;
			activeShader->UseShader();
			activeShader->SetMat4("u_ViewProjection", s_Data.ViewProjectionMatrix);
			activeShader->SetInt("u_Diffuse", cmd.Material->GetDiffuse()->GetTextureSlot());
			activeShader->SetFloat("u_Tiling", cmd.Material->GetTiling());
			break;

		case ViewMode::Depth:
			activeShader = s_Data.DepthShader;
			activeShader->UseShader();
			activeShader->SetMat4("u_ViewProjection", s_Data.ViewProjectionMatrix);
			activeShader->SetFloat("u_Near", 0.1f);
			activeShader->SetFloat("u_Far", 1000.0f);
			break;

		case ViewMode::Shadow:
			break;
		default:
			break;
		}

		activeShader->SetMat4("u_Model", cmd.Transform);
		s_Data.RendererAPI->DrawIndexed(cmd.VAO);
	}
	s_Data.RenderQueue.clear();

	if (s_Data.ActiveSkybox)
	{
		Mat4 viewNoTranslation = Mat4(Mat3(s_Data.ViewMatrix));
		Mat4 skyboxVP = s_Data.ProjectionMatrix * viewNoTranslation;
		s_Data.RendererAPI->SetDepthFunc(Firebox::APIEnum::API_GEQUAL);
		s_Data.ActiveSkybox->GetMaterial()->BindMaterial();
		s_Data.ActiveSkybox->GetShader()->UseShader();
		s_Data.ActiveSkybox->GetShader()->SetMat4("u_ViewProjection", skyboxVP);
		s_Data.RendererAPI->DrawIndexed(s_Data.ActiveSkybox->GetVertexArray());
		s_Data.RendererAPI->SetDepthFunc(Firebox::APIEnum::API_GREATER);
		s_Data.ActiveSkybox = nullptr;
	}
}

void Firebox::Renderer3D::RenderShadowPass()
{
	const auto lightMatrices = s_Data.ShadowMap->GetLightSpaceMatrices();
	s_Data.RendererAPI->ClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	s_Data.RendererAPI->SetDepthFunc(Firebox::APIEnum::API_LESS);
	s_Data.RendererAPI->ClearDepth(1.0f);
	s_ShadowUniformBuffer->BindUniformBuffer();
	for (size_t i = 0; i < lightMatrices.size(); i++)
	{
		s_Data.RendererAPI->BufferSubData(Firebox::APIEnum::API_UNIFORM_BUFFER, i * sizeof(Mat4), sizeof(Mat4), &lightMatrices[i]);
	}
	s_ShadowUniformBuffer->UnbindUniformBuffer();

	s_Data.RendererAPI->CullFace(Firebox::APIEnum::API_BACK);
	s_Data.ShadowDepthShader->UseShader();

	s_Data.ShadowMap->BindShadowMap();
		
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


