#pragma once

#include "Engine/Core/Core.h"

#include <deque>

#define FIREBOX_CONSOLE_PRINT(message) ::Firebox::Console::AddDebugMessage(message)
		
namespace Firebox {

	class FIREBOX_API Console
	{
	private:
		static std::deque<String> s_Messages;

	public:
		static const std::deque<String>& GetMessages();

		static void AddDebugMessage(const String& message);
		static void ClearConsole();
	};
}