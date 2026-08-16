#pragma once

#include "Utils/Types.h"

#include <imgui.h>

namespace EditorUI {

	class FloatParameters
	{
	public:
		static void Int1(int* otherInt, const char* label);
		static void Float1(float* otherFloat, const char* label);
		static void Float2(Vector2* otherVector, const char* label);
		static void Float3(Vector3* otherVector, const char* label);
		static void DrawFloatParameter(const char* text, const char* groupLabel, Vector4 color, float* parameter, bool labelBox);
		static void DrawIntParameter(const char* text, const char* groupLabel, Vector4 color, int* parameter, bool labelBox);
	};
}