#pragma once

#include "Utils/Types.h"

#include <imgui.h>

namespace EditorUI {

	class FloatParameters
	{
	public:
		static void Float3(Vector3* otherVector, const char* label);
		static void DrawParameter(const char* text, const char* groupLabel, Vector4 color, float* parameter);
	};
}