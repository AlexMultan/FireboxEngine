#pragma once

#include "Core/Core.h"
#include "BufferLayout.h"

namespace Firebox {

	class FIREBOX_API VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;
		virtual void BindBuffer() const = 0;
		virtual void UnbindBuffer() const = 0;
		virtual void SetBufferData(const void* data, uint size) = 0;
		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual uint GetBufferID() const = 0;
		static Ref<VertexBuffer> Create(uint size);
		static Ref<VertexBuffer> Create(const void* vertices, uint size);
	};
}