#pragma once

#include "Engine/Core/Core.h"
#include <Engine/Rendering/Resources/Framebuffer.h>

namespace FireboxEditor {

	class ViewportPanel
	{
	private:
		String m_Name = "Viewport";
		uint m_TextureID;
		Vector2 m_ViewportSize{ 0.0f, 0.0f };
		Vector2 m_PendingViewportSize = Vector2(0.0f, 0.0f);
		bool m_IsFocused = false;
		float m_CameraSpeed = 0.05f;
		float m_MenuBarHeight = 0.0f;

	public:
		ViewportPanel();
		ViewportPanel(const char* name);
		~ViewportPanel();

		void RenderViewport(const Ref<Firebox::Framebuffer>& framebuffer);

		inline const Vector2& GetViewportSize()
		{
			return m_ViewportSize;
		}

		inline bool IsFocused() const
		{
			return m_IsFocused;
		}

		inline const float GetCamaraSpeedParameter() const
		{
			return m_CameraSpeed;
		}

		inline void SetMenuBarHeight(float height)
		{
			m_MenuBarHeight = height;
		}
	};
}