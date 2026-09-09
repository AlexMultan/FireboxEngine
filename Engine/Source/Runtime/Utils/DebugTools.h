#pragma once

#include "Core/Core.h"
#include "Core/CoreMinimal.h"

#include <deque>

#define FB_CONSOLE_PRINT(msg) ::Firebox::Console::AddDebugMessage(msg)
#define FB_COUNT_DRAW_CALL ::Firebox::Console::AddDrawCall()
		
namespace Firebox {

	class FIREBOX_API Console
	{
	private:
		static std::deque<String> s_Messages;
		static uint s_DrawCalls;

	public:
		static const std::deque<String>& GetMessages();
		static const uint GetDrawCalls();

		static void AddDebugMessage(const String& message);
		static void AddDrawCall();
		static void SetDrawCalls(uint count);
		static void ClearConsole();
	};
}