#pragma once

#include "Engine/Rendering/API/RendererAPI.h"
#include "Engine/Layers/Layer.h"

namespace Firebox {

	class FIREBOX_API Renderer2D
	{
	private:
		RendererAPI* m_RendererAPI;

	public:
		Renderer2D();
		~Renderer2D();

		void Render();

		inline RendererAPI* GetRendererAPI()
		{
			return m_RendererAPI;
		}
	};
}