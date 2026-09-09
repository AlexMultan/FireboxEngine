#pragma once

#include <filesystem>
#include <string_view>

#include "Core/Core.h"
#include "Core/CoreMinimal.h"

namespace FireboxEditor::EditorContent {

	FIREBOX_API void Init();

	FIREBOX_API std::filesystem::path Get(std::string_view relativePath);
	FIREBOX_API std::filesystem::path GetRootPath();
}