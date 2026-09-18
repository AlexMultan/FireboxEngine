#pragma once

#include "Utils/Types.h"

#include <imgui.h>

namespace EditorUI {

	class FloatParameters
	{
	public:
		static void Checkbox(bool* otherBool, const char* label);
		static bool Int1(int* otherInt, const char* label);
		static bool Float1(float* otherFloat, const char* label);
		static bool Float2(Vector2* otherVector, const char* label);
		static bool Float3(Vector3* otherVector, const char* label);
		static bool Float4(Vector4* otherVector, const char* label);
		static bool DrawFloatParameter(const char* text, const char* groupLabel, Vector4 color, float* parameter, bool labelBox);
		static bool DrawIntParameter(const char* text, const char* groupLabel, Vector4 color, int* parameter, bool labelBox);
		static void DrawCheckbox(const char* text, const char* groupLabel, Vector4 color, bool* parameter);
		
	private:
		static bool DrawFloatComponents(float* components, int count, const char* const* labels, const char* groupLabel);
		
	private:
		// Color definitions for the parameter components (X, Y, Z, W) and their corresponding colors (Red, Green, Blue, Gray)
		static constexpr Vector4 s_ComponentColors[4] = {
			Vector4(0.611f, 0.0f, 0.0f, 1.0f), // Red - X/R
			Vector4(0.02f, 0.58f, 0.0f, 1.0f), // Green - Y/G
			Vector4(0.0f, 0.466f, 1.0f, 1.0f), // Blue - Z/B
			Vector4(0.4f, 0.4f, 0.4f, 1.0f)    // Gray - W/A
		};
	};
}