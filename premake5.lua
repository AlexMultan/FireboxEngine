workspace "FireboxEngine"
    architecture "x64"

    configurations{
        "Debug",
        "Release",
        "Shipping"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["SDL"] = "FireboxEngine/vendor/SDL/include"
IncludeDir["Glad"] = "FireboxEngine/vendor/Glad/include"
IncludeDir["imgui"] = "FireboxEngine/vendor/ImGui"
IncludeDir["glm"] = "FireboxEngine/vendor/GLM"

include "FireboxEngine/vendor/Glad"
include "FireboxEngine/vendor/ImGui"

project "FireboxEngine"
    location "FireboxEngine"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "fireboxpch.h"
    pchsource "FireboxEngine/src/fireboxpch.cpp"

    files{
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs{
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.SDL}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.imgui}",
        "%{IncludeDir.glm}",
        "%{prj.name}/src"
    }

    removefiles{
        "%{prj.name}/vendor/GLM/glm/glm.cppm"
    }

    links{
        "SDL3",
        "opengl32.lib",
        "Glad",
        "imgui"
    }

    libdirs{
        "%{prj.name}/vendor/SDL/lib/x64"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines{
            "FIREBOX_PLATFORM_WIN64",
            "FIREBOX_BUILD_DLL"
        }

        postbuildcommands{
            "{MKDIR} %{wks.location}bin/" .. outputdir .. "/Game",
            "{COPYFILE} %{cfg.buildtarget.relpath} %{wks.location}bin/" .. outputdir .. "/Game",
            "{COPYFILE} %{wks.location}%{prj.name}/vendor/SDL/lib/x64/SDL3.dll %{wks.location}bin/" .. outputdir .. "/Game"
        }

        links {
            "imm32"
        }
        
        filter "configurations:Debug or Release"
            kind "SharedLib"
            defines "FIREBOX_BUILD_DLL"

        filter "configurations:Shipping"
            kind "StaticLib"
            defines "FIREBOX_STATIC"

        filter "configurations:Debug"
            defines "FIREBOX_DEBUG"
            symbols "On"
            buildoptions "/MDd"

        filter "configurations:Release"
            defines "FIREBOX_RELEASE"
            optimize "On"
            buildoptions "/MD"

        filter "configurations:Shipping"
            defines "FIREBOX_SHIPPING"
            optimize "On"
            buildoptions "/MDd"

        filter {"system:windows"}  
            buildoptions "/utf-8"

project "Game"
    location "Game"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
    files{
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    links{
        "FireboxEngine"
    }

    includedirs{
        "FireboxEngine/vendor/spdlog/include",
        "FireboxEngine/vendor/SDL/include",
        "FireboxEngine/vendor/GLM",
        "FireboxEngine/vendor/ImGui",
        "FireboxEngine/src"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines{
            "FIREBOX_PLATFORM_WIN64"
        }

        links {
            "imm32"
        }

        filter "configurations:Debug"
            defines "FIREBOX_DEBUG"
            symbols "On"
            buildoptions "/MDd"

        filter "configurations:Release"
            defines "FIREBOX_RELEASE"
            optimize "On"
            buildoptions "/MD"

        filter "configurations:Shipping"
            defines "FIREBOX_SHIPPING"
            optimize "On"
            buildoptions "/MD"

        filter {"system:windows"}  
            buildoptions "/utf-8"