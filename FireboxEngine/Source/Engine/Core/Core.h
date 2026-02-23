#pragma once

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

#define BIT(x) (1 << x)