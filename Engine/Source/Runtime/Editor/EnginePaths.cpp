#include "EnginePaths.h"
#include "Core/FileSystem.h"

namespace Firebox::EngineContent {

	static std::filesystem::path g_RootDirectory;
	static std::filesystem::path g_ContentRoot;
	static std::filesystem::path g_ShadersRoot;

	void Init()
	{
		g_RootDirectory = Firebox::FileSystem::GoUpDirectories(Firebox::FileSystem::GetExecutableDir(), 3);
		g_ContentRoot = Firebox::FileSystem::GoUpDirectories(Firebox::FileSystem::GetExecutableDir(), 3) / "Resources" / "EngineContent";
		g_ShadersRoot = Firebox::FileSystem::GoUpDirectories(Firebox::FileSystem::GetExecutableDir(), 3) / "Engine" / "Shaders";
	}

	std::filesystem::path GetRoot(std::string_view relativePath)
	{
		return (g_RootDirectory / relativePath).lexically_normal();
	}

	std::filesystem::path Get(std::string_view relativePath)
	{
		return (g_ContentRoot / relativePath).lexically_normal();
	}

	std::filesystem::path Shaders(std::string_view relativePath)
	{
		return (g_ShadersRoot / relativePath).lexically_normal();
	}

	FIREBOX_API std::filesystem::path GetEngineRootPath()
	{
		return g_ContentRoot.lexically_normal();
	}

}