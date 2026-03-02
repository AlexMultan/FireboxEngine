#pragma once
#include "Engine/Core/Log.h"

#include <iostream>

#define ASSERT(condition, message)\
	if(!(condition))\
	{\
		FIREBOX_CORE_ASSERT_LOG("ASSERTION: {0} | {1} | {2}:{3}", #condition, message, __FILE__, __LINE__);\
		__debugbreak();\
	}

#define ASSERT_EDITOR(condition, message)\
	if(!(condition))\
	{\
		FIREBOX_EDITOR_ASSERT_LOG("ASSERTION: {0} | {1} | {2}:{3}", #condition, message, __FILE__, __LINE__);\
		__debugbreak();\
	}