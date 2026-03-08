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

	public:
		ViewportPanel();
		ViewportPanel(const char* name, uint textureID);
		~ViewportPanel();

		virtual void RenderPanel() override;

		inline const Vector2& GetWindowSize()
		{
			return m_ViewportSize;
		}
	};
}