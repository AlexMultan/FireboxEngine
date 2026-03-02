#pragma once

#include "Engine/Core/Core.h"

#include <vector>
#include <string>

#define FIREBOX_CONSOLE_PRINT(message)\
	do{\
		if(Firebox::Console::GetDebugCount() > 0){\
			Firebox::Console::IncreaseDebugCount();\
			Firebox::Console::AddDebugMessage(message);\
		}\
	}while(0)
		
namespace Firebox {

	class FIREBOX_API Console
	{
	private:
		static size_t s_MessageCount;
		static std::vector<std::string> s_Messages;

	public:
		static void Init();

		inline static size_t GetDebugCount()
		{
			return s_MessageCount;
		}

		static const std::vector<std::string>& GetMessages();

		inline static void IncreaseDebugCount()
		{
			s_MessageCount++;
		}

		static void AddDebugMessage(const std::string& message);
		static void ClearConsole();
	};
}