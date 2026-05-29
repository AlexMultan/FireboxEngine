#pragma once

#include "Engine/Rendering/RendererAPI.h"

namespace Firebox {

	class FIREBOX_API Renderer3D
	{
	private:
		RendererAPI* m_RendererAPI;

	public:
		Renderer3D();
		~Renderer3D();

		void OnTick(float deltaTime);
		void OnRender();

		inline RendererAPI* GetRendererAPI()
		{
			return m_RendererAPI;
		}
	};
}