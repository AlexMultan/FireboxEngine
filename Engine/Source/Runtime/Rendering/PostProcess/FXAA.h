#pragma once

#include "Core/Core.h"
#include "Core/CoreMinimal.h"

namespace Firebox {

	struct FXAAInfo
	{
		uint Width;
		uint Height;
	};

	class FIREBOX_API FXAA : public RefCounted
	{
	public:
		virtual ~FXAA() = default;

		virtual void BindFXAABuffer() = 0;
		virtual void UnbindFXAABuffer() = 0;
		virtual void ResizeFXAABuffer(uint width, uint height) = 0;
		virtual uint GetFXAAColorBuffer() = 0;
		virtual void BindSceneTexture(uint textureID, uint textureUnit) = 0;
		virtual void BlitToFramebuffer(uint destinationFramebufferID) = 0;

		static Ref<FXAA> Create();
	};
}