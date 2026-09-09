#pragma once

#include "Vector.h"
#include "Utils/Types.h"

namespace Mathf {

#pragma region Constants

	constexpr float PI = 3.14159f;

	static inline float Deg2Rad(float angle)
	{
		return (PI / 180.0f) * angle;
	}

	static inline float Rad2Deg(float angle)
	{
		return (180.0f / PI) * angle;
	}

#pragma endregion

#pragma region Rounding & Approximation

	static inline float Ceil(float a)
	{
		int trancated = int(a);

		if (a == trancated)
			return a;

		if (a > 0)
			return static_cast<float>(trancated + 1);
		else
			return static_cast<float>(trancated);
	}

	static inline double Ceil(double a)
	{
		int trancated = int(a);

		if (a == trancated)
			return a;

		if (a > 0)
			return static_cast<double>(trancated + 1);
		else
			return static_cast<double>(trancated);
	}

	static inline int CeilToInt(float a)
	{
		int trancated = static_cast<int>(a);

		if (a == trancated)
			return a;

		if (a > 0)
			return trancated + 1;
		else
			return trancated;
	}

	static inline float Floor(float a)
	{
		int trancated = static_cast<int>(a);

		if (a == trancated)
			return a;

		if (a > 0)
			return static_cast<float>(trancated - 1);
		else
			return static_cast<float>(trancated);
	}

	static inline double Floor(double a)
	{
		int trancated = int(a);

		if (a == trancated)
			return a;

		if (a > 0)
			return static_cast<double>(trancated - 1);
		else
			return static_cast<double>(trancated);
	}

	static inline int FloorToInt(float a)
	{
		int trancated = int(a);

		if (a == trancated)
			return a;

		if (a > 0)
			return trancated - 1;
		else
			return trancated;
	}

	static inline float Round(float a)
	{

	}

	static inline int RoundToInt(float a)
	{

	}

	static inline float Approximately(float a, float b)
	{

	}

#pragma endregion

	static inline float DotProduct(const Vector2& a, const Vector2& b)
	{
		return (a.x * b.x) + (a.y * b.y);
	}

	static inline float DotProduct(const Vector3& a, const Vector3& b)
	{
		return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	}

	static inline const Vector3& CrossProduct(const Vector3& a, const Vector3& b)
	{
		auto x = (a.y * b.z) - (a.z * b.y);
		auto y = (a.z * b.x) - (a.x * b.z);
		auto z = (a.x * b.y) - (a.y * b.x);
		return { x, y, z };
	}

#pragma region Interpolation & Movement

	static inline float Lerp(float a, float b, float alpha)
	{
		return a + (b - a) * alpha;
	}
	
	static inline float LerpInverse(float a, float b, float alpha)
	{
		return (alpha - a) / (b - a);
	}

	static inline Vector3 Slerp(const Vector3& a, const Vector3& b, float alpha)
	{
		float omega = acos(DotProduct(a, b));
		return ((sin((1 - alpha) * omega) / sin(omega)) * a) + (sin(alpha * omega)) / sin(omega) * b;
	}

	static inline float Magnitude(const Vector2& vec)
	{
		return static_cast<float>(abs(sqrt(pow(vec.x, 2) + pow(vec.y, 2))));
	}

	static inline float Magnitude(const Vector3& vec)
	{
		return static_cast<float>(abs(sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2))));
	}

	static inline float Distance(const Vector2& a, const Vector2& b)
	{
		return static_cast<float>(sqrt((pow((b.x - a.x), 2) + pow((b.y - a.y), 2))));
	}

	static inline float Distance(const Vector3& a, const Vector3& b)
	{
		return static_cast<float>(sqrt((pow((b.x - a.x), 2) + pow((b.y - a.y), 2) + pow((b.z - a.z), 2))));
	}

#pragma endregion

}