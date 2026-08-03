#include "Skybox.h"
#include "Editor/EnginePaths.h"

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

	m_SkyboxShader = Shader::Create(Firebox::EngineContent::Get("Shaders/GLSL/Skybox.vert").string().c_str(), 
		Firebox::EngineContent::Get("Shaders/GLSL/Skybox.frag").string().c_str(), nullptr);

	m_SkyboxMaterial = CreateRef<Firebox::Material>(m_SkyboxShader);
	m_Faces = {
		Firebox::EngineContent::Get("Textures/Skybox/T_Cubemap_Sky_PartlyCloudy_right.png").string(),
		Firebox::EngineContent::Get("Textures/Skybox/T_Cubemap_Sky_PartlyCloudy_left.png").string(),
		Firebox::EngineContent::Get("Textures/Skybox/T_Cubemap_Sky_PartlyCloudy_top.png").string(),
		Firebox::EngineContent::Get("Textures/Skybox/T_Cubemap_Sky_PartlyCloudy_bottom.png").string(),
		Firebox::EngineContent::Get("Textures/Skybox/T_Cubemap_Sky_PartlyCloudy_front.png").string(),
		Firebox::EngineContent::Get("Textures/Skybox/T_Cubemap_Sky_PartlyCloudy_back.png").string()
	};
	m_SkyboxMaterial->SetCubemapTexture(Firebox::Texture::CreateCubemap(m_Faces));
}

Firebox::Skybox::Skybox(const std::vector<String>& faces)
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

	m_SkyboxShader = Shader::Create(Firebox::EngineContent::Get("Shaders/GLSL/Skybox.vert").string().c_str(),
		Firebox::EngineContent::Get("Shaders/GLSL/Skybox.frag").string().c_str(), nullptr);

	m_SkyboxMaterial = CreateRef<Firebox::Material>(m_SkyboxShader);
	m_SkyboxMaterial->SetCubemapTexture(Firebox::Texture::CreateCubemap(faces));
}
