#pragma once

#include <filesystem>
#include <string_view>

#include "Core/Core.h"

namespace Firebox::EngineContent {

	FIREBOX_API void Init();

	FIREBOX_API std::filesystem::path GetRoot(std::string_view relativePath);
	FIREBOX_API std::filesystem::path Get(std::string_view relativePath);
	FIREBOX_API std::filesystem::path Shaders(std::string_view relativePath);
	FIREBOX_API std::filesystem::path GetEngineRootPath();
}