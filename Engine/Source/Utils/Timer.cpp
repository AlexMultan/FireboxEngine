#include "Timer.h"

float Firebox::Timer::s_TotalTime = 0.0f;

Firebox::Timer::Timer() : m_LastTime(0), m_Frequency(0)
{
	m_LastTime = SDL_GetPerformanceCounter();
	m_Frequency = SDL_GetPerformanceFrequency();
}

Firebox::Timer::~Timer()
{

}

void Firebox::Timer::Tick()
{
	uint64 currentTime = SDL_GetPerformanceCounter();

	m_DeltaTime = (currentTime - m_LastTime) / (double)m_Frequency;
	m_LastTime = currentTime;
	s_TotalTime += m_DeltaTime;
}
