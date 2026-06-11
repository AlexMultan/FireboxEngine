#include "Renderer3D.h"
#include "Engine/Core/Log.h"
#include "Engine/Platform/OpenGL/Shaders/BaseShader.h"
#include "Engine/Utils/Assert.h"

Firebox::Renderer3D::Renderer3DData Firebox::Renderer3D::s_Data;
Ref<Firebox::Grid> Firebox::Renderer3D::s_Grid = nullptr;
Ref<Firebox::Shader> Firebox::Renderer3D::GetBaseShader() { return s_Data.BaseShader; }
Ref<Firebox::Shader> Firebox::Renderer3D::GetLightShader() { return s_Data.LightShader; }
Ref<Firebox::Shader> Firebox::Renderer3D::GetGridShader() { return s_Data.GridShader; }

void Firebox::Renderer3D::Init()
{
	FIREBOX_CORE_TRACE("Renderer3D::Init() called");
	FIREBOX_CORE_TRACE("Renderer3D::Init start");
	s_Data.RendererAPI = RendererAPI::Create();
	ASSERT(s_Data.RendererAPI, "RendererAPI is null!");
	s_Data.RendererAPI->Init();
	FIREBOX_CORE_TRACE("Creating BaseShader...");
	s_Data.BaseShader = Shader::CreateFromSource(Firebox::Shaders::GLSL::BaseVertex, Firebox::Shaders::GLSL::BaseFragment);
	s_Data.LightShader = Shader::CreateFromSource(Firebox::Shaders::GLSL::LightVertex, Firebox::Shaders::GLSL::LightFragment);
	s_Data.GridShader = Shader::CreateFromSource(Firebox::Shaders::GLSL::GridVertexShader, Firebox::Shaders::GLSL::GridFragmentShader);
	ASSERT(s_Data.BaseShader, "BaseShader is null after creation!");
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
	s_Data.ViewProjectionMatrix = camera.GetProjectionMatrix() * camera.GetViewMatrix();
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
	//DrawGrid();
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

	if(s_Grid)[[likely]]
		s_Data.RendererAPI->DrawIndexed(s_Grid->GetVertexArray());
}

void Firebox::Renderer3D::Flush()
{
	for(auto& cmd : s_Data.RenderQueue)
	{
		cmd.Material->BindMaterial();

		s_Data.BaseShader->UseShader();
		s_Data.BaseShader->SetMat4("u_ViewProjection", s_Data.ViewProjectionMatrix);
		s_Data.BaseShader->SetVector3("u_ViewPos", s_Data.CameraPosition);
		
		s_Data.BaseShader->SetVector3("u_DirectionalLight.direction", s_Data.DirectionalLight.Direction);
		s_Data.BaseShader->SetVector3("u_DirectionalLight.ambient", s_Data.DirectionalLight.Color * 0.2f);
		s_Data.BaseShader->SetVector3("u_DirectionalLight.diffuse", s_Data.DirectionalLight.Color);
		s_Data.BaseShader->SetVector3("u_DirectionalLight.specular", s_Data.DirectionalLight.Color);

		auto activeShader = cmd.Material->GetShader();
		activeShader->SetMat4("u_Model", cmd.Transform);
		activeShader->SetMat3("u_InverseNormal", cmd.InverseNormal);
		s_Data.RendererAPI->DrawIndexed(cmd.VAO);
	}
	s_Data.RenderQueue.clear();
}
