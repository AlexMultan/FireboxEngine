#pragma once

#include "Engine/Utils/Types.h"

namespace Utils {

	static inline const String ToString(const Vector2& vec2)
	{
		return "(" + std::to_string(vec2.x) + ", " + std::to_string(vec2.y) + ")";
	}

	static inline const String ToString(const Vector3& vec3)
	{
		return "(" + std::to_string(vec3.x) + ", " + std::to_string(vec3.y) + ", " + std::to_string(vec3.z) + ")";
	}

	static inline const String ToString(const Vector4& vec4)
	{
		return "(" + std::to_string(vec4.x) + ", " + std::to_string(vec4.y) + ", " + std::to_string(vec4.z) + ", " + std::to_string(vec4.w) + ")";
	}
}