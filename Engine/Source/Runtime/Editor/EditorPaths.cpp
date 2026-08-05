#include "EditorPaths.h"
#include "Core/FileSystem.h"

namespace FireboxEditor::EditorContent {

	static std::filesystem::path g_ResourceRoot;

	void Init()
	{
		g_ResourceRoot = Firebox::FileSystem::GoUpDirectories(Firebox::FileSystem::GetExecutableDir(), 3) / "Resources" / "EditorContent";
	}

	std::filesystem::path Get(std::string_view relativePath)
	{
		return (g_ResourceRoot / relativePath).lexically_normal();
	}

	std::filesystem::path GetRootPath()
	{
		return g_ResourceRoot.lexically_normal();
	}

}