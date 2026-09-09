#pragma once

#include "Core/Core.h"
#include "Core/CoreMinimal.h"
#include "Texture.h"
#include "Shader.h"

namespace Firebox {

	enum class MaterialType
	{

	};

	class FIREBOX_API Material : public RefCounted
	{
	public:
		Material();
		Material(const Ref<Shader>& shader);

		void BindTextures() const;
		void BindMaterial() const;
		void BindMaterial(const Ref<Shader>& targetShader) const;

		inline void SetDiffuseTexture(const Ref<Texture>& texture) { m_DiffuseTexture = texture; }
		inline void SetRoughnessTexture(const Ref<Texture>& texture) { m_RoughnessTexture = texture; }
		inline void SetNormalTexture(const Ref<Texture>& texture) { m_NormalTexture = texture; }
		inline void SetMetallicTexture(const Ref<Texture>& texture) { m_MetallicTexture = texture; }
		inline void SetCubemapTexture(const Ref<Texture>& cubemap) { m_CubemapTexture = cubemap; }
		inline void SetDiffuseColor(const Vector4& color) { m_DiffuseColor = color; }
		inline void SetRoughnessValue(const float value) { m_RougnessValue = value; }
		inline void SetMetallicValue(const float value) { m_MetallicValue = value; }

		inline const Ref<Shader>& GetShader() const { return m_Shader; }
		inline const Ref<Texture>& GetDiffuse() const { return m_DiffuseTexture; }
		inline const Ref<Texture>& GetRoughness() const { return m_RoughnessTexture; }
		inline const Ref<Texture>& GetNormal() const { return m_NormalTexture; }
		inline const Ref<Texture>& GetMetallic() const { return m_MetallicTexture; }
		inline const Ref<Texture>& GetCubemap() const { return m_CubemapTexture; }
		inline Vector4& GetDiffuseColor() { return m_DiffuseColor; }
		inline float& GetRoughnessValue() { return m_RougnessValue; }
		inline const float GetMetallicValue() const { return m_MetallicValue; }

	private:
		Ref<Shader> m_Shader;
		Ref<Texture> m_DiffuseTexture;
		Ref<Texture> m_RoughnessTexture;
		Ref<Texture> m_NormalTexture;
		Ref<Texture> m_MetallicTexture;
		Ref<Texture> m_CubemapTexture;
		Vector4 m_DiffuseColor{ 0.7f, 0.7f, 0.7f, 1.0f };
		float m_RougnessValue = 0.5f;
		float m_MetallicValue = 0.0f;
	};
}