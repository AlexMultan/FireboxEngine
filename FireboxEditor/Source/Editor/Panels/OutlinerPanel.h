#pragma once

#include "Engine/Core/Core.h"
#include "Editor/Panels/IPanel.h"

namespace FireboxEditor {

	class OutlinerPanel : public IPanel
	{
	private:
		String m_Name = "Outliner";
		bool m_IsActive = true;

	public:
		OutlinerPanel();
		OutlinerPanel(const char* name);
		~OutlinerPanel();

		virtual void RenderPanel() override;

		inline const bool GetIsActive() const
		{
			return m_IsActive;
		}
	};
}