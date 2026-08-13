#pragma once

#include "Core/Core.h"

#include <type_traits>

namespace Firebox {

	enum class APIEnum : uint
	{
		// Masks
		API_DEPTH_BUFFER_BIT = 1 << 0,
		API_STENCIL_BUFFER_BIT = 1 << 1,
		API_COLOR_BUFFER_BIT = 1 << 2,

		// Booleans
		API_FALSE,
		API_TRUE,

		// Primitive types
		API_POINTS,
		API_LINES,
		API_LINE_LOOP,
		API_LINE_STRIP,
		API_TRIANGLES,
		API_TRIANGLE_STRIP,
		API_TRIANGLE_FAN,
		API_QUADS,

		// Depth/stencil comparison functions
		API_NEVER,
		API_LESS,
		API_EQUAL,
		API_LEQUAL,
		API_GREATER,
		API_NOTEQUAL,
		API_GEQUAL,
		API_ALWAYS,

		// Blend factors
		API_ZERO,
		API_ONE,
		API_SRC_COLOR,
		API_ONE_MINUS_SRC_COLOR,
		API_SRC_ALPHA,
		API_ONE_MINUS_SRC_ALPHA,
		API_DST_ALPHA,
		API_ONE_MINUS_DST_ALPHA,
		API_DST_COLOR,
		API_ONE_MINUS_DST_COLOR,
		API_SRC_ALPHA_SATURATE,

		API_FRAMEBUFFER,
		API_UNIFORM_BUFFER,

		API_BACK,
		API_FRONT,

		API_BLEND,
		API_DEPTH_TEST,
		API_CULL_FACE,
		API_DITHER,
		API_MULTISAMPLE,
		API_STENCIL_TEST,
		API_SCISSOR_TEST
	};

	inline constexpr APIEnum operator|(APIEnum lApiEnum, APIEnum rApiEnum)
	{
		return static_cast<APIEnum>(
			static_cast<std::underlying_type_t<APIEnum>>(lApiEnum) | 
			static_cast<std::underlying_type_t<APIEnum>>(rApiEnum)
			);
	}

	inline constexpr APIEnum operator&(APIEnum lApiEnum, APIEnum rApiEnum)
	{
		return static_cast<APIEnum>(
			static_cast<std::underlying_type_t<APIEnum>>(lApiEnum) &
			static_cast<std::underlying_type_t<APIEnum>>(rApiEnum)
			);
	}
}