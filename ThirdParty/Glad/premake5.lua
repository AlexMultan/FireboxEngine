project "Glad"
	kind "StaticLib"
	language "C"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files{
		"include/glad/glad.h",
        "include/KHR/khrplatform.h",
        "src/glad.c"
	}

    includedirs{
        "include"
    }

    filter "action:vs2022"
        toolset "msc"

    filter "action:gmake"
        toolset "clang"
        buildoptions {
            "-Wall",
            "-Wextra"
        }


    filter "system:windows"
        systemversion "latest"
        staticruntime "On"

        filter {"system:windows", "configurations:Release"}
            buildoptions "/MT"
