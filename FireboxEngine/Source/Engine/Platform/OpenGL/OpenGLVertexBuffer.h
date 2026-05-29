#pragma once

#include "glad/glad.h"
#include <cstdio>
#include <iostream>

namespace Firebox {

	class OpenGLVertexBuffer
	{
	private:
		uint32_t m_RendererID;

	public:
		OpenGLVertexBuffer(size_t bufferSize, const void* data);
		~OpenGLVertexBuffer();

		inline uint32_t GetRendererID() const
		{
			return m_RendererID;
		}

		void BindBuffer() const;
		void UnbindBuffer() const;
	};
}