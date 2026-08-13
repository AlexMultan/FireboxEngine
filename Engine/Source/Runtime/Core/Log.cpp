#include "Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include "spdlog/sinks/rotating_file_sink.h"
#include "Filesystem.h"

namespace Firebox {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;
	std::shared_ptr<spdlog::logger> Log::s_EditorLogger;

	std::filesystem::path savedPath = Firebox::FileSystem::GoUpDirectories(Firebox::FileSystem::GetExecutableDir(), 3) / "Saved";

	std::filesystem::path Get(std::string_view relativePath)
	{
		return (savedPath / relativePath).lexically_normal();
	}

	void Log::Init()
	{
		spdlog::set_pattern("*** [%H:%M:%S %z] [%n] [%^-%l-%$] [thread %t] %v ***");

		auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		consoleSink->set_level(spdlog::level::trace);

		size_t maxFileSize = 1048576 * 5;
		size_t maxBackupFiles = 3;

		auto coreFileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(Get("Engine/Logs/FireboxEngine.log").string(), maxFileSize, maxBackupFiles);
		coreFileSink->set_level(spdlog::level::trace);

		auto clientFileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(Get("Project/Logs/Project.log").string(), maxFileSize, maxBackupFiles);
		clientFileSink->set_level(spdlog::level::trace);

		auto editorFileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(Get("Editor/Logs/FireboxEditor.log").string(), maxFileSize, maxBackupFiles);
		editorFileSink->set_level(spdlog::level::trace);

		std::vector<spdlog::sink_ptr> coreSinks{ consoleSink, coreFileSink };
		s_CoreLogger = std::make_shared<spdlog::logger>("ENGINE", coreSinks.begin(), coreSinks.end());
		s_CoreLogger->set_level(spdlog::level::trace);
		spdlog::register_logger(s_CoreLogger);

		std::vector<spdlog::sink_ptr> clientSinks{ consoleSink, clientFileSink };
		s_ClientLogger = std::make_shared<spdlog::logger>("PROJECT", clientSinks.begin(), clientSinks.end());
		s_ClientLogger->set_level(spdlog::level::trace);
		spdlog::register_logger(s_ClientLogger);

		std::vector<spdlog::sink_ptr> editorSinks{ consoleSink, editorFileSink };
		s_EditorLogger = std::make_shared<spdlog::logger>("EDITOR", editorSinks.begin(), editorSinks.end());
		s_EditorLogger->set_level(spdlog::level::trace);
		spdlog::register_logger(s_EditorLogger);

		spdlog::flush_every(std::chrono::seconds(3));
	}
}