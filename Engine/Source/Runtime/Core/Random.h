#pragma once

#include "Core.h"

#include <type_traits>
#include <random>
#include <limits>

namespace Firebox {

	class FIREBOX_API Random
	{
	public:
		Random() = delete;

		static void Seed(uint64 seed)
		{
			Engine().seed(seed);
		}

		template<typename T>
		static T Range(T min, T max)
		{
			static_assert(std::is_arithmetic<T>::value, "Random::Range requires a numeric value!");

			if constexpr (std::is_integral<T>::value)
			{
				std::uniform_int_distribution<T> dist(min, max);
				return dist(Engine());
			}
			else
			{
				std::uniform_real_distribution<T> dist(min, max);
				return dist(Engine());
			}
		}

		template<typename T = float>
		static T Value()
		{
			static_assert(std::is_floating_point<T>::value, "Random::Value requires a floating point number!");
			return Range<T>(T(0), T(1));
		}

		static bool Bool(double trueChance = 0.5)
		{
			return Value<double>() < trueChance;
		}

	private:
		static std::mt19937_64& Engine()
		{
			static thread_local std::mt19937_64 engine{ std::random_device{}() };
			return engine;
		}
	};
}