#pragma once
 
#ifdef _MSC_VER
	#pragma warning(disable: 4251)
#endif
 
#ifdef FIREBOX_PLATFORM_WIN64
	#ifdef FIREBOX_BUILD_DLL
		#define FIREBOX_API __declspec(dllexport)
	#elif defined(FIREBOX_STATIC)
		#define FIREBOX_API
	#else
		#define FIREBOX_API __declspec(dllimport)
	#endif
#elif defined(FIREBOX_PLATFORM_LINUX)
	#ifdef FIREBOX_BUILD_DLL
		#define FIREBOX_API __attribute__((visibility("default")))
	#elif defined(FIREBOX_STATIC)
		#define FIREBOX_API
	#else
		#define FIREBOX_API
	#endif
#else
	#error Firebox Engine only supports Windows and Linux
#endif


#if defined(_MSC_VER)
	#define FB_DEBUG_BREAK() __debugbreak()
#elif defined(__clang__)
	#define FB_DEBUG_BREAK() __builtin_debugtrap()
#else
	#include <signal>
	#define FB_DEBUG_BREAK() raise(SIGTRAP)
#endif