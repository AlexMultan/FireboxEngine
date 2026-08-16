#pragma once

#include "Vector.h"
#include "Utils/Types.h"

namespace Mathf {

	static inline float DotProduct(const Vector2& a, const Vector2& b)
	{
		return (a.x * b.x) + (a.y * b.y);
	}

	static inline float DotProduct(const Vector3& a, const Vector3& b)
	{
		return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	}

	static inline float Lerp(float a, float b, float alpha)
	{
		return a + (b - a) * alpha;
	}

	static inline Vector3 Slerp(const Vector3& a, const Vector3& b, float alpha)
	{
		float omega = acos(DotProduct(a, b));
		return ((sin((1 - alpha) * omega) / sin(omega)) * a) + (sin(alpha * omega)) / sin(omega) * b;
	}

	static inline float Magnitude(const Vector2& vec)
	{
		return abs(sqrt(pow(vec.x, 2) + pow(vec.y, 2)));
	}

	static inline float Magnitude(const Vector3& vec)
	{
		return abs(sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2)));
	}

	static inline float Distance(const Vector2& a, const Vector2& b)
	{
		return sqrt((pow((b.x - a.x), 2) + pow((b.y - a.y), 2)));
	}

	static inline float Distance(const Vector3& a, const Vector3& b)
	{
		return sqrt((pow((b.x - a.x), 2) + pow((b.y - a.y), 2) + pow((b.z - a.z), 2)));
	}
}