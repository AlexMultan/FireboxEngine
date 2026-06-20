project "ImGuizmo"
	kind "StaticLib"
	language "C++"
	staticruntime "Off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs{
		"src",
		"../ImGui"
	}

    filter "system:windows"
        systemversion "latest"

        filter {"system:windows", "configurations:Release"}
            buildoptions "/MT"
