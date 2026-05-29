#include "DebugTools.h"
#include "Engine/Core/Log.h"

std::deque<String> Firebox::Console::s_Messages;

const std::deque<String>& Firebox::Console::GetMessages()
{
	return s_Messages;
}

void Firebox::Console::AddDebugMessage(const String& message)
{
	s_Messages.push_front(message);
}

void Firebox::Console::ClearConsole()
{
	s_Messages.clear();
}
