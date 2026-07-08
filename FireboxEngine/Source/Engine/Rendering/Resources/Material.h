#pragma once

#include "Engine/Core/Core.h"
#include "Texture.h"
#include "Shader.h"

namespace Firebox {

	enum class MaterialType
	{

	};

	class FIREBOX_API Material
	{
	public:
		Material();
		Material(const Ref<Shader>& shader);

		void BindTextures() const;
		void BindMaterial() const;

		inline void SetDiffuseTexture(const Ref<Texture>& texture) { m_DiffuseTexture = texture; }
		inline void SetSpecularTexture(const Ref<Texture>& texture) { m_SpecularTexture = texture; }
		inline void SetNormalTexture(const Ref<Texture>& texture) { m_NormalTexture = texture; }
		inline void SetCubemapTexture(const Ref<Texture>& cubemap) { m_CubemapTexture = cubemap; }
		inline void SetShininess(float shininess) { m_Shininess = shininess; }
		inline void SetTiling(float tiling) { m_Tiling = tiling; }

		inline const Ref<Shader>& GetShader() const { return m_Shader; }
		inline const Ref<Texture>& GetDiffuse() const { return m_DiffuseTexture; }
		inline const Ref<Texture>& GetNormal() const { return m_NormalTexture; }
		inline const Ref<Texture>& GetCubemap() const { return m_CubemapTexture; }
		inline float& GetShininess() { return m_Shininess; }
		inline float& GetTiling() { return m_Tiling; }

	private:
		Ref<Shader> m_Shader;
		Ref<Texture> m_DiffuseTexture;
		Ref<Texture> m_SpecularTexture;
		Ref<Texture> m_NormalTexture;
		Ref<Texture> m_CubemapTexture;
		float m_Shininess = 256.0f;
		float m_Tiling = 1.0f;
	};
}