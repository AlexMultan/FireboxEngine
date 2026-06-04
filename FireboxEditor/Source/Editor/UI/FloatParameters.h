#pragma once

#include "Engine/Utils/Types.h"

#include <imgui.h>

namespace FireboxEditor {

	class FloatParameters
	{
	public:
		void Float3(Vector3* otherVector, const char* label, ImFont* font);

	private:
		void DrawParameter(const char* text, const char* groupLabel, Vector4 color, float* parameter, ImFont* font);
	};
}