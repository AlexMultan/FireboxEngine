#pragma once

#include "Editor/Panels/IPanel.h"
#include "Engine/Core/Core.h"

namespace FireboxEditor {

	class Debugger : public IPanel
	{
	public:
		Debugger();
		~Debugger();

		virtual void RenderPanel () override;
	};
}