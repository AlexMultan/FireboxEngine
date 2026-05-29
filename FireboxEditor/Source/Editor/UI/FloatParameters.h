#pragma once

#include "Engine/Utils/Types.h"

namespace FireboxEditor {

	class FloatParameters
	{
	public:
		void Float3(Vector3* otherVector, const char* label);

	private:
		void DrawParameter(const char* text, const char* groupLabel, Vector4 color, float* parameter);
	};
}