physxdir = "physx"

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

	for _, mod in ipairs(physxmodules) do
        local base = physxdir .. "/" .. mod

        files{
            base .. "/**.cpp",
            base .. "/**.h"
        }

        includedirs { base }
        for _, dir in ipairs(os.matchdirs(base .. "/**")) do
            includedirs { dir }
        end
    end

    includedirs { physxdir .. "/include" }
    for _, dir in ipairs(os.matchdirs(physxdir .. "/include/**")) do
        includedirs { dir }
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