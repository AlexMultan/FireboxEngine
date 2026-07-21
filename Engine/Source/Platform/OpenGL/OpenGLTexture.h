#pragma once

#include "Rendering/Resources/Texture.h"

namespace Firebox {

	class FIREBOX_API OpenGLTexture : public Texture
	{
	public:
		OpenGLTexture(const String& path);
		OpenGLTexture(const DynamicArray<String>& faces);
		~OpenGLTexture();

		virtual void BindTexture(uint slot) override;
		virtual void BindCubemapTexture(uint slot) override;
		virtual void UnbindTexture() override;
		virtual void UnbindCubemapTexture() override;
		virtual void DeleteTexture() override;

		virtual uint GetTextureID() const override { return m_TextureID; }

	private:
		uint m_TextureID = 0;
		uint m_CubemapTextureID = 0;
		uint m_TextureSlot = 0;
	};
}