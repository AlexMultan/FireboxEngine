#pragma once

#include "glad/glad.h"

#include <vector>
#include <cstdio>
#include <iostream>

namespace Firebox {

	struct OpenGLVertexBufferElement
	{
		uint32_t type, count;
		unsigned char normalized;
	};

	class OpenGLVertexBufferLayout
	{
	private:
		std::vector<OpenGLVertexBufferElement> m_Elements;
		uint32_t m_Stride;

	public:
		OpenGLVertexBufferLayout() : m_Stride(0) {};
		~OpenGLVertexBufferLayout() {};

		template<typename T>
		void Push(uint32_t count)
		{
			static_assert(false);
		}

		template<>
		void Push<float>(uint32_t count)
		{
			m_Elements.push_back({ GL_FLOAT, (uint32_t)count, GL_FALSE });
			m_Stride += count * sizeof(GL_FLOAT);
		}

		template<>
		void Push<uint32_t>(uint32_t count)
		{
			m_Elements.push_back({ GL_UNSIGNED_INT, (uint32_t)count, GL_FALSE });
			m_Stride += count * sizeof(GL_UNSIGNED_INT);
		}

		template<>
		void Push<unsigned char>(uint32_t count)
		{
			m_Elements.push_back({ GL_BYTE, (uint32_t)count, GL_TRUE });
			m_Stride += count * sizeof(GLbyte);
		}

		inline const std::vector<OpenGLVertexBufferElement>& GetElements() const
		{
			return m_Elements;
		}

		inline const uint32_t GetStride() const
		{
			return m_Stride;
		}
	};
}