#include "EditorPaths.h"
#include "Core/FileSystem.h"

namespace FireboxEditor::Paths {

	static std::filesystem::path g_ResourceRoot;

	void Init()
	{
		g_ResourceRoot = Firebox::FileSystem::GoUpDirectories(Firebox::FileSystem::GetExecutableDir(), 3) / "Editor" / "Resources";
	}

	std::filesystem::path Resource(std::string_view relativePath)
	{
		return (g_ResourceRoot / relativePath).lexically_normal();
	}

	std::filesystem::path GetRootPath()
	{
		return g_ResourceRoot.lexically_normal();
	}

}