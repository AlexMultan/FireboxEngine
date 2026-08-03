#pragma once

#include "Utils/Types.h"
#include "Utils/Timer.h"

#ifdef FIREBOX_PLATFORM_WIN64
	#ifdef FIREBOX_BUILD_DLL
		#define FIREBOX_API __declspec(dllexport)
	#elif defined(FIREBOX_STATIC)
		#define FIREBOX_API
	#else
		#define FIREBOX_API __declspec(dllimport)
	#endif
#else
	#error Firebox Engine only supports Windows(for now)
#endif



#if defined(_MSC_VER)
	#define FB_DEBUG_BREAK() __debugbreak()
#elif defined(__clang__)
	#define FB_DEBUG_BREAK() __builtin_debugtrap()
#else
	#include <signal>
	#define FB_DEBUG_BREAK() raise(SIGTRAP)
#endif