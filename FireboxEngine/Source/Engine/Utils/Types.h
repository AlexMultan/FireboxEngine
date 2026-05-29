#pragma once

#include <glm/glm.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <concepts>

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint;
typedef uint64_t uint64;

using String = std::string;

template<typename T>
using DynamicArray = std::vector<T>;

template<typename T>
using Ref = std::shared_ptr<T>;

template<typename T>
using Scope = std::unique_ptr<T>;

template<typename T, typename... Args>
constexpr Ref<T> CreateRef(Args&&... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}

template<typename T, typename... Args>
constexpr Scope<T> CreateScope(Args&&... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}

using Vector2 = glm::vec2;
using Vector3 = glm::vec3;
using Vector4 = glm::vec4;
using Mat2 = glm::mat2;
using Mat3 = glm::mat3;
using Mat4 = glm::mat4;

namespace Utils {

	static inline bool InRange(float value, float min, float max)
	{
		return value >= min && value <= max;
	}

	static inline bool InRange(int value, int min, int max)
	{
		return value >= min && value <= max;
	}

	static inline bool InRange(double value, double min, double max)
	{
		return value >= min && value <= max;
	}

	static inline bool InRange(const Vector2& value, const Vector2& min, const Vector2& max)
	{
		return value.x >= min.x && value.x <= max.x && value.y >= min.y && value.y <= max.y;
	}
}