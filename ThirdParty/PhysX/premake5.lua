physxdir = path.getabsolute("physx")

physxmodules = {
	"source/foundation",
	"source/common",
	"source/fastxml",
	"source/filebuf",
	"source/geomutils",
	"source/lowlevel",
	"source/lowlevelaabb",
	"source/lowleveldynamics",
	"source/physx",
	"source/physxcommon",
	"source/physxcooking",
	"source/physxextensions",
	"source/physxcharacterkinematic",
	"source/physxvehicle",
	"source/physxvehicle2",
	"source/physxmetadata/core",
	"source/physxmetadata/extensions",
	"source/pvd",
	"source/scenequery",
	"source/simulationcontroller",
	"source/immediatemode",
	"source/task"
}

project "PhysX"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "Off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files{}

	includedirs { physxdir .. "/include" }

	for _, mod in ipairs(physxmodules) do
    local base = physxdir .. "/" .. mod

    files{
        base .. "/**.cpp",
        base .. "/**.h"
    }
    includedirs { base }

    for _, dir in ipairs(os.matchdirs(base .. "/**")) do
        local lower = dir:lower()
        local isWindowsDir = lower:find("/windows") or lower:find("\\windows")
        local isUnixDir    = lower:find("/unix")    or lower:find("\\unix")
        local isLinuxDir   = lower:find("/linux")   or lower:find("\\linux")
        local isMacDir     = lower:find("/mac")     or lower:find("\\mac")

        filter "system:windows"
            if not (isUnixDir or isLinuxDir or isMacDir) then
                includedirs { dir }
            end
        filter "system:linux"
            if not (isWindowsDir or isMacDir) then
                includedirs { dir }
            end
        filter "system:macosx"
            if not (isWindowsDir or isUnixDir or isLinuxDir) then
                includedirs { dir }
            end
        filter {}
    end
end

	includedirs { physxdir .. "/source/physxgpu/include" }
    includedirs { physxdir .. "/pvdruntime/include" }

	defines{
		"PX_PHYSX_STATIC_LIB",
		"PX_SUPPORT_PVD=1"
	}

	filter "action:vs2022"
		toolset "msc"

	filter "action:gmake"
		toolset "clang"
		buildoptions { "-I" .. physxdir .. "/include" }
		for _, mod in ipairs(physxmodules) do
			buildoptions { "-I" .. physxdir .. "/" .. mod }
		end
	filter {}

	filter "system:windows"
		systemversion "latest"
        characterset "MBCS"
		defines { "WIN32", "_WINDOWS" }
		removefiles{
        physxdir .. "/**/unix/**",
        physxdir .. "/**/linux/**",
        physxdir .. "/**/mac/**"
    }

	filter "system:linux"
		defines { "PX_LINUX" }
		pic "On"
		removefiles{
            physxdir .. "/**/windows/**",
            physxdir .. "/**/mac/**"
        }

	filter "system:macosx"
		removefiles{
            physxdir .. "/**/windows/**",
            physxdir .. "/**/linux/**",
            physxdir .. "/**/unix/**"
        }

	filter "configurations:Debug"
		defines { "_DEBUG", "PX_DEBUG=1", "PX_CHECKED=1" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"