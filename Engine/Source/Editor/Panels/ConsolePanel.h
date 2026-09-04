#pragma once

#include "Panels/IPanel.h"
#include "Core/CoreMinimal.h"

namespace FireboxEditor {

	class ConsolePanel : public IPanel
	{
	public:
		ConsolePanel();
		~ConsolePanel();

		virtual void RenderPanel() override;
	};
}