#pragma once

#include "Core/Core.h"

namespace Firebox {

	class FIREBOX_API UniformBuffer
	{
	public:
		virtual void BindUniformBuffer() = 0;
		virtual void UnbindUniformBuffer() = 0;
		static Ref<UniformBuffer> Create();
	};
}