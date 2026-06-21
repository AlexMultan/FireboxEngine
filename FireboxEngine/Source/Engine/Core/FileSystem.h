#pragma once

#include <filesystem>

#if defined(_WIN32)
	#define NOMINMAX
	#include <Windows.h>
#elif defined(__APPLE__)
	#include <mach-o/dyld.h>
	#include <climits>
	#include <cstdint>
#elif defined(__linux__)
	#include <unistd.h>
	#include <climits>
	#include <vector>
#endif

namespace Firebox::FileSystem {

	inline std::filesystem::path GoUpDirectories(std::filesystem::path path, uint32_t count)
	{
		for (uint32_t i = 0; i < count; i++)
			path = path.parent_path();

		return path;
	}

	inline std::filesystem::path GetExecutableDir()
	{
#if defined(_WIN32)
		wchar_t buffer[MAX_PATH];
		DWORD len = GetModuleFileNameW(nullptr, buffer, MAX_PATH);
		if (len == 0 || len == MAX_PATH)
			return {};
		return std::filesystem::path(buffer).parent_path();

#elif defined(__APPLE__)
		char buffer[PATH_MAX];
		uint32_t size = sizeof(buffer);
		if (_NSGetExecutablePath(buffer, &size) != 0)
			return {};
		return std::filesystem::canonical(buffer).parent_path();

#elif defined(__linux__)
		std::error_code ec;
		auto path = std::filesystem::canonical("/proc/self/exe", ec);
		if (ec)
			return {};
		return path.parent_path();

#else
#error "GetExecutableDir() not implemented for this platform"
#endif

	}
}