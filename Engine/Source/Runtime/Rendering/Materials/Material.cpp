#include "Material.h"
#include "Rendering/Renderer3D.h"

Firebox::Material::Material()
{
	m_Shader = Firebox::Renderer3D::GetGBufferShader();
}

Firebox::Material::Material(const Ref<Shader>& shader) : m_Shader(shader)
{
	
}

void Firebox::Material::BindTextures() const
{
	if (m_DiffuseTexture)
		m_DiffuseTexture->BindTexture(0);

	if (m_RoughnessTexture)
		m_RoughnessTexture->BindTexture(1);

	if (m_NormalTexture)
		m_NormalTexture->BindTexture(2);

	if (m_MetallicTexture)
		m_MetallicTexture->BindTexture(3);

	if (m_CubemapTexture)
		m_CubemapTexture->BindCubemapTexture(4);
}

void Firebox::Material::BindMaterial() const
{
	BindMaterial(m_Shader);
}

void Firebox::Material::BindMaterial(const Ref<Shader>& targetShader) const
{
	targetShader->UseShader();
	BindTextures();
	if (m_DiffuseTexture)
	{
		targetShader->SetBool("u_Material.hasDiffuse", true);
		targetShader->SetInt("u_Material.diffuse", 0);
	}
	else
	{
		targetShader->SetBool("u_Material.hasDiffuse", false);
		targetShader->SetVector4("u_Material.diffuseColor", m_DiffuseColor);
	}

	if (m_RoughnessTexture)
	{
		targetShader->SetBool("u_Material.hasRoughness", true);
		targetShader->SetInt("u_Material.roughness", 1);
	}
	else
	{
		targetShader->SetBool("u_Material.hasRoughness", false);
		targetShader->SetFloat("u_Material.roughnessValue", m_RougnessValue);
	}

	if (m_NormalTexture)
		targetShader->SetInt("u_Material.normal", 2);

	if (m_MetallicTexture)
	{
		targetShader->SetBool("u_Material.hasMetallic", true);
		targetShader->SetInt("u_Material.metallic", 3);
	}
	else
	{
		targetShader->SetBool("u_Material.hasMetallic", false);
		targetShader->SetFloat("u_Material.metallicValue", m_MetallicValue);
	}

	if (m_CubemapTexture)
		targetShader->SetInt("u_SkyboxTex", 4);
}