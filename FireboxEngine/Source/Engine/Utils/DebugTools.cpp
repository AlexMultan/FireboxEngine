#include "DebugTools.h"

size_t Firebox::Console::s_MessageCount;
std::vector<std::string> Firebox::Console::s_Messages;

void Firebox::Console::Init()
{
	s_Messages.clear();
	s_MessageCount = 1;
}

const std::vector<std::string>& Firebox::Console::GetMessages()
{
	return s_Messages;
}

void Firebox::Console::AddDebugMessage(const std::string& message)
{
	s_Messages.reserve(s_MessageCount);
	s_Messages.emplace_back(message);
}

void Firebox::Console::ClearConsole()
{
	s_Messages.clear();
	s_MessageCount = 1;
}
