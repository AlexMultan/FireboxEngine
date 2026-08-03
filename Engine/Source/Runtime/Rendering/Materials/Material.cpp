#include "Material.h"
#include "Rendering/Renderer3D.h"

Firebox::Material::Material()
{
	m_Shader = Firebox::Renderer3D::GetLitShader();
}

Firebox::Material::Material(const Ref<Shader>& shader) : m_Shader(shader)
{
	
}

void Firebox::Material::BindTextures() const
{
	if (m_DiffuseTexture)
		m_DiffuseTexture->BindTexture(0);

	if (m_SpecularTexture)
		m_SpecularTexture->BindTexture(1);

	if (m_NormalTexture)
		m_NormalTexture->BindTexture(2);

	if (m_CubemapTexture)
		m_CubemapTexture->BindCubemapTexture(3);
}

void Firebox::Material::BindMaterial() const
{
	m_Shader->UseShader();
	BindTextures();
	if (m_DiffuseTexture)
		m_Shader->SetInt("u_Material.diffuse", 0);

	if (m_SpecularTexture)
		m_Shader->SetInt("u_Material.specular", 1);

	if (m_NormalTexture)
		m_Shader->SetInt("u_Material.normal", 2);

	if (m_CubemapTexture)
		m_Shader->SetInt("u_SkyboxTex", 3);
	else
	{
		m_Shader->SetFloat("u_Material.shininess", m_Shininess);
		m_Shader->SetFloat("u_Tiling", m_Tiling);
	}
}
