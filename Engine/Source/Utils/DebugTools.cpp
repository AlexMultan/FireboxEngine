#include "DebugTools.h"
#include "Core/Log.h"

std::deque<String> Firebox::Console::s_Messages;
uint Firebox::Console::s_DrawCalls;

const std::deque<String>& Firebox::Console::GetMessages()
{
	return s_Messages;
}

const uint Firebox::Console::GetDrawCalls()
{
	return s_DrawCalls;
}

void Firebox::Console::AddDebugMessage(const String& message)
{
	s_Messages.push_front(message);
}

void Firebox::Console::AddDrawCall()
{
	s_DrawCalls += 1;
}

void Firebox::Console::SetDrawCalls(uint count)
{
	s_DrawCalls = count;
}

void Firebox::Console::ClearConsole()
{
	s_Messages.clear();
}
