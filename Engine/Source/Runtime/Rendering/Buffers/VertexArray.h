#pragma once

#include "Core/Core.h"
#include "Core/CoreMinimal.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Firebox {
	class FIREBOX_API VertexArray : public RefCounted
	{
	public:
		virtual ~VertexArray() = default;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;
		virtual uint GetID() = 0;
		
		static Ref<VertexArray> Create();
	};
}