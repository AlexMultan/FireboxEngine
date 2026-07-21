#pragma once

#include "Rendering/Resources/UniformBuffer.h"

namespace Firebox::OpenGL {
	class FIREBOX_API OpenGLUniformBuffer : public UniformBuffer
	{
	public:
		OpenGLUniformBuffer();
		~OpenGLUniformBuffer();

		virtual void BindUniformBuffer() override;
		virtual void UnbindUniformBuffer() override;

	private:
		uint m_UBO;
	};
}