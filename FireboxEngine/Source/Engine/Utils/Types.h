#pragma once

#include <glm/glm.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <memory>

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

namespace Utilities {

	static inline const String ToString(const Vector2& vec2)
	{
		return "(" + std::to_string(vec2.x) + ", " + std::to_string(vec2.y) + ")";
	}

	static inline const String& ToString(const Vector3& vec3)
	{
		return "(" + std::to_string(vec3.x) + ", " + std::to_string(vec3.y) + ", " + std::to_string(vec3.z);
	}
}

