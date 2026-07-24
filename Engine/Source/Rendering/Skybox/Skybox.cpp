#include "Skybox.h"
#include "Editor/EngineAssets.h"
#include "Rendering/Backends/Shaders/GLSL/DefaultShader.h"

Firebox::Skybox::Skybox()
{
	m_VAO = VertexArray::Create();
	m_VAO->Bind();
	m_VBO = VertexBuffer::Create(vertices, sizeof(vertices));
	m_VBO->SetLayout({
		{ ShaderDataType::Float3, "aPos" }
		});

	m_IBO = IndexBuffer::Create(indices, 36);
	m_VAO->AddVertexBuffer(m_VBO);
	m_VAO->SetIndexBuffer(m_IBO);
	m_VAO->Unbind();

	m_SkyboxShader = Shader::CreateFromSource(Firebox::Shaders::GLSL::SkyboxVertexShader, Firebox::Shaders::GLSL::SkyboxFragmentShader, nullptr);

	m_SkyboxMaterial = CreateRef<Firebox::Material>(m_SkyboxShader);
	m_Faces = {
		Firebox::EngineAssets::Get("Textures/Skybox/T_Cubemap_Sky_PartlyCloudy_right.png").string(),
		Firebox::EngineAssets::Get("Textures/Skybox/T_Cubemap_Sky_PartlyCloudy_left.png").string(),
		Firebox::EngineAssets::Get("Textures/Skybox/T_Cubemap_Sky_PartlyCloudy_top.png").string(),
		Firebox::EngineAssets::Get("Textures/Skybox/T_Cubemap_Sky_PartlyCloudy_bottom.png").string(),
		Firebox::EngineAssets::Get("Textures/Skybox/T_Cubemap_Sky_PartlyCloudy_front.png").string(),
		Firebox::EngineAssets::Get("Textures/Skybox/T_Cubemap_Sky_PartlyCloudy_back.png").string()
	};
	m_SkyboxMaterial->SetCubemapTexture(Firebox::Texture::CreateCubemap(m_Faces));
}

Firebox::Skybox::Skybox(const DynamicArray<String>& faces)
{
	m_VAO = VertexArray::Create();
	m_VAO->Bind();
	m_VBO = VertexBuffer::Create(vertices, sizeof(vertices));
	m_VBO->SetLayout({
		{ ShaderDataType::Float3, "aPos" }
		});

	m_IBO = IndexBuffer::Create(indices, 36);
	m_VAO->AddVertexBuffer(m_VBO);
	m_VAO->SetIndexBuffer(m_IBO);
	m_VAO->Unbind();

	m_SkyboxShader = Shader::CreateFromSource(Firebox::Shaders::GLSL::SkyboxVertexShader, Firebox::Shaders::GLSL::SkyboxFragmentShader, nullptr);

	m_SkyboxMaterial = CreateRef<Firebox::Material>(m_SkyboxShader);
	m_SkyboxMaterial->SetCubemapTexture(Firebox::Texture::CreateCubemap(faces));
}
