#pragma once

#include "Engine/Utils/Types.h"

#include <SDL3/SDL_timer.h>

namespace Firebox
{
	class Timer
	{
	private:
		uint64 m_LastTime;
		uint64 m_Frequency;
		float m_DeltaTime;
		static float s_TotalTime;

	public:
		Timer();
		virtual ~Timer();

		void Tick();

		inline const float GetDeltaTime() const
		{
			return m_DeltaTime;
		}

		inline static float GetTotalTime()
		{
			return s_TotalTime;
		}
	};
}