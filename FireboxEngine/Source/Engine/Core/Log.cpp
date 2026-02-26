#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Firebox {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;
	std::shared_ptr<spdlog::logger> Log::s_EditorLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("FIREBOX_ENGINE");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("GAME");
		s_ClientLogger->set_level(spdlog::level::trace);

		s_EditorLogger = spdlog::stdout_color_mt("EDITOR");
		s_EditorLogger->set_level(spdlog::level::trace);
	}
}