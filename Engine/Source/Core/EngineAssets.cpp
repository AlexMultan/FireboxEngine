#include "EngineAssets.h"
#include "FileSystem.h"

namespace Firebox::EngineAssets {

	static std::filesystem::path g_Root;

	void Init()
	{
		g_Root = Firebox::FileSystem::GoUpDirectories(Firebox::FileSystem::GetExecutableDir(), 3) / "Engine" / "EngineAssets";
	}

	std::filesystem::path Get(std::string_view relativePath)
	{
		return (g_Root / relativePath).lexically_normal();
	}

}