#pragma once

#include "Core/Core.h"
#include "Core/CoreMinimal.h"

namespace Firebox {

	class FIREBOX_API UniformBuffer : public RefCounted
	{
	public:
		virtual void BindUniformBuffer() = 0;
		virtual void UnbindUniformBuffer() = 0;
		static Ref<UniformBuffer> Create();
	};
}