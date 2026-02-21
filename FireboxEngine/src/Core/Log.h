#pragma once

#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"

#define FIREBOX_CORE_TRACE(...) ::Firebox::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FIREBOX_CORE_INFO(...)  ::Firebox::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FIREBOX_CORE_WARN(...)  ::Firebox::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FIREBOX_CORE_ERROR(...) ::Firebox::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FIREBOX_CORE_CRITICAL(...) ::Firebox::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define FIREBOX_TRACE(...) ::Firebox::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FIREBOX_INFO(...)  ::Firebox::Log::GetClientLogger()->info(__VA_ARGS__)
#define FIREBOX_WARN(...)  ::Firebox::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FIREBOX_ERROR(...) ::Firebox::Log::GetClientLogger()->error(__VA_ARGS__)
#define FIREBOX_CRITICAL(...) ::Firebox::Log::GetClientLogger()->critical(__VA_ARGS__)


namespace Firebox {

	class FIREBOX_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger()
		{
			return s_CoreLogger;
		}
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger()
		{
			return s_ClientLogger;
		}

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

#pragma once
