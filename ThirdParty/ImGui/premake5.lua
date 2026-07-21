project "imgui"
	kind "StaticLib"
	language "C++"
	staticruntime "Off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files{
		"imconfig.h",
		"imgui_impl_opengl3.h",
		"imgui_impl_opengl3_loader.h",
		"imgui_impl_sdl3.h",
		"imgui_internal.h",
		"imgui.h",
		"imstb_rectpack.h",
		"imstb_textedit.h",
		"imstb_truetype.h",

		"imgui_demo.cpp",
		"imgui_draw.cpp",
		"imgui_impl_opengl3.cpp",
		"imgui_impl_sdl3.cpp",
		"imgui_tables.cpp",
		"imgui_widgets.cpp",
		"imgui.cpp"
	}

	includedirs{
		".",
		"../SDL/include"
	}

    filter "system:windows"
        systemversion "latest"

        filter {"system:windows", "configurations:Release"}
            buildoptions "/MT"
