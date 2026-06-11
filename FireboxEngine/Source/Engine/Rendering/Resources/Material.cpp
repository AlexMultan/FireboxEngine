#include "Material.h"

Firebox::Material::Material(const Ref<Shader>& shader) : m_Shader(shader)
{

}

void Firebox::Material::BindMaterial() const
{
	m_Shader->UseShader();
	if (m_DiffuseTexture)
	{
		m_DiffuseTexture->BindTexture(0);
		m_Shader->SetInt("u_Material.diffuse", 0);
	}

	if (m_SpecularTexture)
	{
		m_SpecularTexture->BindTexture(1);
		m_Shader->SetInt("u_Material.specular", 1);
	}

	m_Shader->SetFloat("u_Material.shininess", m_Shininess);
}
