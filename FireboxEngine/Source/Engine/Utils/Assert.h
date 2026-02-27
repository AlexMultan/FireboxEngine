#pragma once
#include "Engine/Core/Log.h"

#ifdef ASSERT(condition, message)\
	do{\		if(!(condition))\
		{\
		FIREBOX_CORE_ERROR(L"ASSERTION: {0} | {1} | {2}:{3}", #condition, message, __FILE__, __LINE__)\
			__debugbreak()\
		}\
	}while(0)
#else
	#define ASSERT(condition, message)
#endif