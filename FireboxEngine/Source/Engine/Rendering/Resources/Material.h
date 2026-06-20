#pragma once

#include "Engine/Core/Core.h"
#include "Texture.h"
#include "Shader.h"

namespace Firebox {
	class FIREBOX_API Material
	{
	public:
		Material();
		Material(const Ref<Shader>& shader);

		void BindMaterial() const;

		inline void SetDiffuseTexture(const Ref<Texture>& texture) { m_DiffuseTexture = texture; }
		inline void SetSpecularTexture(const Ref<Texture>& texture) { m_SpecularTexture = texture; }
		inline void SetShininess(float shininess) { m_Shininess = shininess; }

		inline const Ref<Shader>& GetShader() const { return m_Shader; }
		inline float GetShininess() const { return m_Shininess; }

	private:
		Ref<Shader> m_Shader;
		Ref<Texture> m_DiffuseTexture;
		Ref<Texture> m_SpecularTexture;
		float m_Shininess = 256.0f;
	};
}