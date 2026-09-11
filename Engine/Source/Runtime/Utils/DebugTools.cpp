#include "DebugTools.h"
#include "Core/Log.h"

std::deque<String> Firebox::Console::s_Messages;
uint Firebox::Console::s_DrawCalls;
size_t Firebox::Console::s_VertexCount;
uint Firebox::Console::s_IndexCount;

const std::deque<String>& Firebox::Console::GetMessages()
{
	return s_Messages;
}

const uint Firebox::Console::GetDrawCalls()
{
	return s_DrawCalls;
}

const size_t Firebox::Console::GetVertexCount()
{
    return s_VertexCount;
}

const uint Firebox::Console::GetIndexCount()
{
    return s_IndexCount;
}

void Firebox::Console::AddDebugMessage(const String& message)
{
	s_Messages.push_front(message);
}

void Firebox::Console::AddDrawCall()
{
	s_DrawCalls++;
}

void Firebox::Console::SetDrawCalls(uint count)
{
	s_DrawCalls = count;
}

void Firebox::Console::AddVertices(size_t count)
{
	s_VertexCount += count;
}

void Firebox::Console::AddIndices(uint count)
{
	s_IndexCount += count;
}

void Firebox::Console::ClearConsole()
{
	s_Messages.clear();
}
