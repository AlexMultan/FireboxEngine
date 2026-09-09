#pragma once

#include "Core/Core.h"
#include "Core/CoreMinimal.h"

namespace Firebox {
	class FIREBOX_API IndexBuffer : public RefCounted
	{
	public:
		~IndexBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual uint GetCount() const = 0;
		virtual uint GetBufferID() const = 0;

		static Ref<IndexBuffer> Create(const uint* indices, uint count);
	};
}