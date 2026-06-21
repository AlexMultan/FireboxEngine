#include "EditorPaths.h"
#include "FileSystem.h"

namespace FireboxEditor::Paths {

	static std::filesystem::path g_ResourceRoot;

	void Init()
	{
		g_ResourceRoot = Firebox::FileSystem::GoUpDirectories(Firebox::FileSystem::GetExecutableDir(), 3) / "FireboxEditor" / "Resources";
	}

	std::filesystem::path Resource(std::string_view relativePath)
	{
		return (g_ResourceRoot / relativePath).lexically_normal();
	}

}