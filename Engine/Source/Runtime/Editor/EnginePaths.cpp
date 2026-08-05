#include "EnginePaths.h"
#include "Core/FileSystem.h"

namespace Firebox::EngineContent {

	static std::filesystem::path g_Root;

	void Init()
	{
		g_Root = Firebox::FileSystem::GoUpDirectories(Firebox::FileSystem::GetExecutableDir(), 3) / "Resources" / "EngineContent";
	}

	std::filesystem::path Get(std::string_view relativePath)
	{
		return (g_Root / relativePath).lexically_normal();
	}

	FIREBOX_API std::filesystem::path GetRootPath()
	{
		return g_Root.lexically_normal();
	}

}