#pragma once

#include "Engine/Core/Core.h"

namespace Firebox {

	class FIREBOX_API Texture
	{
	public:
		virtual ~Texture() = default;

		static Ref<Texture> Create(const String& path);
		static Ref<Texture> CreateCubemap(const DynamicArray<String>& faces);
		virtual void BindTexture(uint slot) = 0;
		virtual void BindCubemapTexture(uint slot) = 0;
		virtual void UnbindTexture() = 0;
		virtual void UnbindCubemapTexture() = 0;
		virtual void DeleteTexture() = 0;

		virtual uint GetTextureID() const = 0;

		inline const String& GetTexturePath() const { return m_TexturePath; }
		void SetTexturePath(const String& path);

	private:
		String m_TexturePath;
	};
}