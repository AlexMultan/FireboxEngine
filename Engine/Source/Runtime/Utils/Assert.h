#pragma once
#include "Core/Log.h"

#include <iostream>

#define FB_ASSERT(condition, message)\
	if(!(condition))\
	{\
		FB_CORE_ASSERT_LOG("ASSERTION: {0} | {1} | {2}:{3}", #condition, message, __FILE__, __LINE__);\
		FB_DEBUG_BREAK();\
	}

#define FB_ASSERT_EDITOR(condition, message)\
	if(!(condition))\
	{\
		FB_EDITOR_ASSERT_LOG("ASSERTION: {0} | {1} | {2}:{3}", #condition, message, __FILE__, __LINE__);\
		FB_DEBUG_BREAK();\
	}