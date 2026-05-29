#pragma once

#include "Engine/Core/Core.h"
#include "Editor/Panels/IPanel.h"

namespace FireboxEditor {

	class ViewportPanel : public IPanel
	{
	private:
		String m_Name = "Viewport";
		uint m_TextureID;
		Vector2 m_ViewportSize;
		bool m_IsFocused = false;
		float m_CameraSpeed = 0.05f;
		float m_MenuBarHeight = 0.0f;

	public:
		ViewportPanel();
		ViewportPanel(const char* name, uint textureID);
		~ViewportPanel();

		virtual void RenderPanel() override;

		inline const Vector2& GetWindowSize()
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