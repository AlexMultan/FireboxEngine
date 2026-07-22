#pragma once

#include <filesystem>
#include <string_view>

#include "Core/Core.h"

namespace FireboxEditor::Paths {

	FIREBOX_API void Init();

	FIREBOX_API std::filesystem::path Resource(std::string_view relativePath);

}