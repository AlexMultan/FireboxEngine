#include "Renderer3D.h"
#include "Engine/Core/Log.h"
#include "Engine/Core/EngineAssets.h"
#include "Engine/Platform/OpenGL/Shaders/DefaultShader.h"
#include "Engine/Platform/OpenGL/Shaders/UnlitShader.h"
#include "Engine/Platform/OpenGL/Shaders/DepthShader.h"
#include "Engine/Utils/Assert.h"

#include <algorithm>
#include <cfloat>
#include <limits>

Firebox::Renderer3D::Renderer3DData Firebox::Renderer3D::s_Data;
Firebox::ViewMode Firebox::Renderer3D::s_ViewMode = Firebox::ViewMode::Lit;
Ref<Firebox::Grid> Firebox::Renderer3D::s_Grid = nullptr;
Ref<Firebox::Skybox> Firebox::Renderer3D::s_Skybox = nullptr;
Ref<Firebox::Shader> Firebox::Renderer3D::GetDefaultShader() { return s_Data.DefaultShader; }
Ref<Firebox::Shader> Firebox::Renderer3D::GetLightShader() { return s_Data.LightShader; }
Ref<Firebox::Shader> Firebox::Renderer3D::GetGridShader() { return s_Data.GridShader; }
const Ref<Firebox::Material>& Firebox::Renderer3D::GetDefaultMaterial() { return s_Data.DefaultMaterial; }
const Ref<Firebox::Material>& Firebox::Renderer3D::GetSkyboxMaterial() { return s_Data.SkyboxMaterial; }
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
	s_Data.DefaultShader = Shader::CreateFromSource(Firebox::Shaders::GLSL::DefaultVertex, Firebox::Shaders::GLSL::DefaultFragment);
	s_Data.UnlitShader = Shader::CreateFromSource(Firebox::Shaders::GLSL::UnlitVertex, Firebox::Shaders::GLSL::UnlitFragment);
	s_Data.DepthShader = Shader::CreateFromSource(Firebox::Shaders::GLSL::DepthVertex, Firebox::Shaders::GLSL::DepthFragment);
	s_Data.ShadowDepthShader = Shader::CreateFromSource(Firebox::Shaders::GLSL::ShadowMapDepthVertex, Firebox::Shaders::GLSL::ShadowMapDepthFragment);
	s_Data.ShadowMap = ShadowMap::Create(2048, 2048);
	s_Data.LightShader = Shader::CreateFromSource(Firebox::Shaders::GLSL::LightVertex, Firebox::Shaders::GLSL::LightFragment);
	s_Data.GridShader = Shader::CreateFromSource(Firebox::Shaders::GLSL::GridVertexShader, Firebox::Shaders::GLSL::GridFragmentShader);
	s_Data.SkyboxShader = Shader::CreateFromSource(Firebox::Shaders::GLSL::SkyboxVertexShader, Firebox::Shaders::GLSL::SkyboxFragmentShader);

	s_Data.DefaultMaterial = CreateRef<Material>(s_Data.DefaultShader);
	s_Data.DefaultMaterial->SetDiffuseTexture(Firebox::Texture::Create(Firebox::EngineAssets::Get("Textures/medieval_red_brick_diff_2k.png").string()));
	s_Data.DefaultMaterial->SetSpecularTexture(Firebox::Texture::Create(Firebox::EngineAssets::Get("Textures/medieval_red_brick_diff_2k.png").string()));
	s_Data.DefaultMaterial->SetNormalTexture(Firebox::Texture::Create(Firebox::EngineAssets::Get("Textures/medieval_red_brick_nor_gl_2k.png").string()));

	s_Data.SkyboxMaterial = CreateRef<Material>(s_Data.SkyboxShader);
	DynamicArray<String> skyboxFaces{
		Firebox::EngineAssets::Get("Textures/Skybox/T_Cubemap_Sky_PartlyCloudy_right.png").string(),
		Firebox::EngineAssets::Get("Textures/Skybox/T_Cubemap_Sky_PartlyCloudy_left.png").string(),
		Firebox::EngineAssets::Get("Textures/Skybox/T_Cubemap_Sky_PartlyCloudy_top.png").string(),
		Firebox::EngineAssets::Get("Textures/Skybox/T_Cubemap_Sky_PartlyCloudy_bottom.png").string(),
		Firebox::EngineAssets::Get("Textures/Skybox/T_Cubemap_Sky_PartlyCloudy_front.png").string(),
		Firebox::EngineAssets::Get("Textures/Skybox/T_Cubemap_Sky_PartlyCloudy_back.png").string()
	};
	s_Data.SkyboxMaterial->SetCubemapTexture(Firebox::Texture::CreateCubemap(skyboxFaces));

	FB_ASSERT(s_Data.DefaultShader, "BaseShader is null after creation!");
	s_Grid = CreateRef<Firebox::Grid>();
	s_Skybox = CreateRef<Firebox::Skybox>();
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
	s_Data.ViewMatrix = camera.GetViewMatrix();
	s_Data.ProjectionMatrix = camera.GetPerspective();
	s_Data.DirectionalLight = directionalLight;

	s_Data.RenderQueue.clear();
}

void Firebox::Renderer3D::EndScene()
{
	std::sort(s_Data.RenderQueue.begin(), s_Data.RenderQueue.end(), [](const RenderCommand& a, const RenderCommand& b)
		{
			return a.Material->GetShader()->GetID() < b.Material->GetShader()->GetID();
		});
	//RenderShadowPass();
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

void Firebox::Renderer3D::DrawSkybox()
{
	Mat4 viewNoTranslation = Mat4(Mat3(s_Data.ViewMatrix));
	Mat4 skyboxVP = s_Data.ProjectionMatrix * viewNoTranslation;
	s_Data.RendererAPI->SetDepthFunc(Firebox::APIEnum::API_GEQUAL);
	s_Data.SkyboxMaterial->BindMaterial();
	s_Data.SkyboxShader->UseShader();
	s_Data.SkyboxShader->SetMat4("u_ViewProjection", skyboxVP);
	if (s_Skybox)
		s_Data.RendererAPI->DrawIndexed(s_Skybox->GetVertexArray());
	s_Data.RendererAPI->SetDepthFunc(Firebox::APIEnum::API_GREATER);
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

			activeShader->SetMat4("u_LightSpaceMatrix", s_Data.LightSpaceMatrix);

			//s_Data.RendererAPI->BindTexture(4, s_Data.ShadowMap->GetDepthTexture());
			//activeShader->SetInt("u_ShadowMap", 4);
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

void Firebox::Renderer3D::RenderShadowPass()
{
	auto frustumCorners = GetFrustumCornersWorldSpace(s_Data.ViewProjectionMatrix);

	Vector3 center(0.0f);
	for (auto& corner : frustumCorners)
		center += corner;
	center /= frustumCorners.size();

	Vector3 lightDir = glm::normalize(s_Data.DirectionalLight.Direction);
	Mat4 lightView = glm::lookAt(center - lightDir * 50.0f, center, Vector3(0.0f, 1.0f, 0.0f));

	float minX = FLT_MAX, maxX = -FLT_MAX;
	float minY = FLT_MAX, maxY = -FLT_MAX;
	float minZ = FLT_MAX, maxZ = -FLT_MAX;

	for (auto& corner : frustumCorners)
	{
		Vector4 lightSpaceCorner = lightView * Vector4(corner, 1.0f);
		minX = std::min(minX, lightSpaceCorner.x);
		maxX = std::max(maxX, lightSpaceCorner.x);
		minY = std::min(minY, lightSpaceCorner.y);
		maxY = std::max(maxY, lightSpaceCorner.y);
		minZ = std::min(minZ, lightSpaceCorner.z);
		maxZ = std::max(maxZ, lightSpaceCorner.z);
	}

	constexpr float zPad = 10.0f;
	Mat4 lightProjection = glm::ortho(minX, maxX, minY, maxY, minZ - zPad, maxZ + zPad);

	s_Data.LightSpaceMatrix = lightProjection * lightView;

	s_Data.ShadowMap->BindFramebuffer();

	s_Data.RendererAPI->SetDepthFunc(APIEnum::API_LESS);
	s_Data.RendererAPI->ClearDepth(1.0f);
	s_Data.RendererAPI->Clear(APIEnum::API_DEPTH_BUFFER_BIT);

	s_Data.ShadowDepthShader->UseShader();
	s_Data.ShadowDepthShader->SetMat4("u_LightSpaceMatrix", s_Data.LightSpaceMatrix);

	for (auto& cmd : s_Data.RenderQueue)
	{
		s_Data.ShadowDepthShader->SetMat4("u_Model", cmd.Transform);
		s_Data.RendererAPI->DrawIndexed(cmd.VAO);
	}

	s_Data.RendererAPI->SetDepthFunc(APIEnum::API_GREATER);
	s_Data.RendererAPI->ClearDepth(0.0f);

	s_Data.ShadowMap->UnbindFramebuffer();
}

std::array<Vector3, 8> Firebox::Renderer3D::GetFrustumCornersWorldSpace(const Mat4& viewProjection)
{
	Mat4 inverse = glm::inverse(viewProjection);

	std::array<Vector3, 8> corners;
	int i = 0;
	for (int x = 0; x < 2; x++)
	{
		for (int y = 0; y < 2; y++)
		{
			for (int z = 0; z < 2; z++)
			{
				Vector4 pt = inverse * Vector4(
					2.0f * x - 1.0f,
					2.0f * y - 1.0f,
					2.0f * z - 1.0f,
					1.0f
				);
				corners[i++] = Vector3(pt) / pt.w;
			}
		}
	}
	return corners;
}
