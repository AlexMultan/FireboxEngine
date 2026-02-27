#pragma once

#include "Engine/Core/Core.h"
#include "Engine/Input/KeyCodes.h"

namespace Firebox {

	class FIREBOX_API Input
	{
	public:
		static bool IsKeyPressed(KeyCode keycode);
		static bool IsMouseButtonPressed(int button);
		static float GetMouseX();
		static float GetMouseY();
	};
}