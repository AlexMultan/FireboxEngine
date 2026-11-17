#pragma once

#include "Core/Core.h"
#include "Core/CoreMinimal.h"

struct ProjectConfig
{
	String Name = "Sandbox";
	std::filesystem::path EditorStartScene;
	std::filesystem::path GameStartScene;
	std::filesystem::path ContentDirectory;
};