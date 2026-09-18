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

	static inline Mat4x4 Inverse(const Mat4x4& matrix)
	{
		return glm::inverse(matrix);
	}

	static inline Vector3 Normalize(const Vector3& vec)
	{
		return glm::normalize(vec);
	}

#pragma endregion

#pragma region Rounding & Approximation

	static inline float Ceil(float a)
	{
		return std::ceil(a);
	}

	static inline double Ceil(double a)
	{
		return std::ceil(a);
	}

	static inline int CeilToInt(float a)
	{
		return static_cast<int>(std::ceil(a));
	}

	static inline float Floor(float a)
	{
		return std::floor(a);
	}

	static inline double Floor(double a)
	{
		return std::floor(a);
	}

	static inline int FloorToInt(float a)
	{
		return static_cast<int>(std::floor(a));
	}

	static inline float Round(float a)
	{
		return std::round(a);
	}

	static inline int RoundToInt(float a)
	{
		return static_cast<int>(std::round(a));
	}

	static inline float Approximately(float a, float b)
	{
		return std::abs(a - b) < std::numeric_limits<float>::epsilon();
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

	static inline Vector3 CrossProduct(const Vector3& a, const Vector3& b)
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
	float sinOmega = sin(omega);

	float coeffA = static_cast<float>(sin((1 - alpha) * omega) / sinOmega);
	float coeffB = static_cast<float>(sin(alpha * omega) / sinOmega);

	return (coeffA * a) + (coeffB * b);
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