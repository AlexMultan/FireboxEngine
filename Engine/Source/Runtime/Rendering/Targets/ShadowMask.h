#pragma once

#include "Core/Core.h"
#include "Core/CoreMinimal.h"

namespace Firebox {

	struct ShadowMaskInfo
	{
		uint Width;
		uint Height;
		uint ShadowMaskTexture;
		uint ShadowMaskFBO;
	};

	class FIREBOX_API ShadowMask : public RefCounted
	{
	public:
		virtual ~ShadowMask() = default;

		virtual void BindShadowMask() = 0;
		virtual void BindShadowMaskTexture() = 0;
		virtual void UnbindShadowMask() = 0;
		virtual void ResizeShadowMask(uint width, uint height) = 0;
		virtual void ClearShadowMask() = 0;

		static Ref<ShadowMask> Create();
	};
}
