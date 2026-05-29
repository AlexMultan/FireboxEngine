#pragma once

#include "glad/glad.h"
#include <cstdio>
#include <iostream>

namespace Firebox {

	class OpenGLIndexBuffer
	{
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;

	public:
		OpenGLIndexBuffer(uint32_t count, const uint32_t* data);
		~OpenGLIndexBuffer();

		inline uint32_t GetRendererID() const
		{
			return m_RendererID;
		}

		inline uint32_t GetCount() const
		{
			return m_Count;
		}

		void BindBuffer() const;
		void UnbindBuffer() const;
	};
}