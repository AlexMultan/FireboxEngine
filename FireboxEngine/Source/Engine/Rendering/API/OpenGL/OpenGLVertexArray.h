#pragma once

#include "OpenGLVertexBuffer.h"
#include "OpenGLVertexBufferLayout.h"

namespace Firebox {

	class OpenGLVertexArray
	{
	private:
		uint32_t m_RendererID;

	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		void AddVertexArray(const OpenGLVertexBuffer& vbo, const OpenGLVertexBufferLayout& layout);
		void Bind() const;
		void Unbind() const;
	};
}