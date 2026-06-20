#pragma once

#include "Engine/Core/Core.h"

namespace Firebox {

	class FIREBOX_API Texture
	{
	public:
		virtual ~Texture() = default;

		static Ref<Texture> Create(const String& path);
		virtual void BindTexture(uint slot) = 0;
		virtual void UnbindTexture() = 0;
		virtual void DeleteTexture() = 0;

		virtual uint GetTextureID() const = 0;
	};
}