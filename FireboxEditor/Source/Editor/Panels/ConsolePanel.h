#pragma once

#include "Editor/Panels/IPanel.h"
#include "Engine/Core/Core.h"

namespace FireboxEditor {

	class ConsolePanel : public IPanel
	{
	public:
		ConsolePanel();
		~ConsolePanel();

		virtual void RenderPanel() override;
	};
}