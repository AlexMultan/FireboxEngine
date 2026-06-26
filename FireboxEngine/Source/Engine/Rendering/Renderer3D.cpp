#include "Renderer3D.h"
#include "Engine/Core/Log.h"
#include "Engine/Core/EngineAssets.h"
#include "Engine/Platform/OpenGL/Shaders/DefaultShader.h"
#include "Engine/Platform/OpenGL/Shaders/UnlitShader.h"
#include "Engine/Platform/OpenGL/Shaders/DepthShader.h"
#include "Engine/Utils/Assert.h"

Firebox::Renderer3D::Renderer3DData Firebox::Renderer3D::s_Data;
Firebox::ViewMode Firebox::Renderer3D::s_ViewMode = Firebox::ViewMode::Lit;
Ref<Firebox::Grid> Firebox::Renderer3D::s_Grid = nullptr;
Ref<Firebox::Shader> Firebox::Renderer3D::GetDefaultShader() { return s_Data.DefaultShader; }
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
	FB_CORE_TRACE("Creating BaseShader...");
	s_Data.DefaultShader = Shader::CreateFromSource(Firebox::Shaders::GLSL::DefaultVertex, Firebox::Shaders::GLSL::DefaultFragment);
	s_Data.UnlitShader = Shader::CreateFromSource(Firebox::Shaders::GLSL::UnlitVertex, Firebox::Shaders::GLSL::UnlitFragment);
	s_Data.DepthShader = Shader::CreateFromSource(Firebox::Shaders::GLSL::DepthVertex, Firebox::Shaders::GLSL::DepthFragment);
	s_Data.LightShader = Shader::CreateFromSource(Firebox::Shaders::GLSL::LightVertex, Firebox::Shaders::GLSL::LightFragment);
	s_Data.GridShader = Shader::CreateFromSource(Firebox::Shaders::GLSL::GridVertexShader, Firebox::Shaders::GLSL::GridFragmentShader);
	s_Data.DefaultMaterial = CreateRef<Material>(s_Data.DefaultShader);
	s_Data.DefaultMaterial->SetDiffuseTexture(Firebox::Texture::Create(Firebox::EngineAssets::Get("Textures/T_DefaultTexture.png").string()));
	s_Data.DefaultMaterial->SetSpecularTexture(Firebox::Texture::Create(Firebox::EngineAssets::Get("Textures/T_DefaultTexture.png").string()));
	FB_ASSERT(s_Data.DefaultShader, "BaseShader is null after creation!");
	s_Grid = CreateRef<Firebox::Grid>();
}

void Firebox::Renderer3D::Shutdown()
{
	s_Data.RenderQueue.clear();
}

void Firebox::Renderer3D::BeginScene(const Camera& camera, const DirectionalLightComponent& directionalLight)
{
	s_Data.RendererAPI->SetScreenColor(Vector4(0.1f, 0.1f, 0.1f, 1.0f));
	s_Data.RendererAPI->Clear();

	s_Data.CameraPosition = camera.GetPosition();
	s_Data.ViewProjectionMatrix = camera.GetPerspective() * camera.GetViewMatrix();
	s_Data.DirectionalLight = directionalLight;

	s_Data.RenderQueue.clear();
}

void Firebox::Renderer3D::EndScene()
{
	std::sort(s_Data.RenderQueue.begin(), s_Data.RenderQueue.end(), [](const RenderCommand& a, const RenderCommand& b)
		{
			return a.Material->GetShader()->GetID() < b.Material->GetShader()->GetID();
		});
	Flush();
	
}

void Firebox::Renderer3D::DrawMesh(const Ref<Mesh>& mesh, const Ref<Material>& material, const TransformComponent& transform)
{
	s_Data.RenderQueue.push_back({ mesh->GetVertexArray(), material, transform.GetTransform(), transform.GetInverseNormal() });
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

void Firebox::Renderer3D::Flush()
{
	for(auto& cmd : s_Data.RenderQueue)
	{
		Ref<Shader> activeShader;

		switch (s_ViewMode)
		{
		case ViewMode::Lit:
			activeShader = s_Data.DefaultShader;
			cmd.Material->BindMaterial();
			activeShader->UseShader();
			activeShader->SetMat4("u_ViewProjection", s_Data.ViewProjectionMatrix);
			activeShader->SetVector3("u_ViewPos", s_Data.CameraPosition);
			activeShader->SetMat3("u_InverseNormal", cmd.InverseNormal);

			activeShader->SetVector3("u_DirectionalLight.direction", s_Data.DirectionalLight.Direction);
			activeShader->SetVector3("u_DirectionalLight.ambient", s_Data.DirectionalLight.Color * 0.2f);
			activeShader->SetVector3("u_DirectionalLight.diffuse", s_Data.DirectionalLight.Color);
			activeShader->SetVector3("u_DirectionalLight.specular", s_Data.DirectionalLight.Color);
			break;

		case ViewMode::Unlit:
			activeShader = s_Data.UnlitShader;
			activeShader->UseShader();
			activeShader->SetMat4("u_ViewProjection", s_Data.ViewProjectionMatrix);
			cmd.Material->BindTextures();
			activeShader->SetInt("u_Diffuse", 0);
			break;

		case ViewMode::Depth:
			activeShader = s_Data.DepthShader;
			activeShader->UseShader();
			activeShader->SetMat4("u_ViewProjection", s_Data.ViewProjectionMatrix);
			activeShader->SetFloat("u_Near", 0.1f);
			activeShader->SetFloat("u_Far", 1000.0f);
			break;

		default:
			break;
		}

		activeShader->SetMat4("u_Model", cmd.Transform);
		s_Data.RendererAPI->DrawIndexed(cmd.VAO);
	}
	s_Data.RenderQueue.clear();
}
