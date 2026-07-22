#pragma once

#include <filesystem>
#include <string_view>

#include "Core/Core.h"

namespace Firebox::EngineAssets {

	FIREBOX_API void Init();

	FIREBOX_API std::filesystem::path Get(std::string_view relativePath);

}