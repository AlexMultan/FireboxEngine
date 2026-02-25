workspace "FireboxEngine"
    architecture "x64"

    configurations{
        "Debug",
        "Release",
        "Shipping"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["SDL"] = "FireboxEngine/ThirdParty/SDL/include"
IncludeDir["Glad"] = "FireboxEngine/ThirdParty/Glad/include"
IncludeDir["imgui"] = "FireboxEngine/ThirdParty/ImGui"
IncludeDir["glm"] = "FireboxEngine/ThirdParty/GLM"

include "FireboxEngine/ThirdParty/Glad"
include "FireboxEngine/ThirdParty/ImGui"

project "FireboxEngine"
    location "FireboxEngine"
    language "C++"

    targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
    objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")

    files{
        "%{prj.name}/Source/Engine/**.h",
        "%{prj.name}/Source/Engine/**.cpp"
    }

    includedirs{
        "%{prj.name}/ThirdParty/spdlog/include",
        "%{IncludeDir.SDL}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.imgui}",
        "%{IncludeDir.glm}",
        "%{prj.name}/Source"
    }

    removefiles{
        "%{prj.name}/ThirdParty/GLM/glm/glm.cppm"
    }

    links{
        "SDL3",
        "opengl32.lib",
        "Glad",
        "imgui"
    }

    libdirs{
        "%{prj.name}/ThirdParty/SDL/lib/x64"
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
            --EDITOR
            "{MKDIR} %{wks.location}Binaries/" .. outputdir .. "/FireboxEditor",
            "{COPYFILE} %{cfg.buildtarget.relpath} %{wks.location}Binaries/" .. outputdir .. "/FireboxEditor",
            "{COPYFILE} %{wks.location}%{prj.name}/ThirdParty/SDL/lib/x64/SDL3.dll %{wks.location}Binaries/" .. outputdir .. "/FireboxEditor",

            --GAME
            "{MKDIR} %{wks.location}Binaries/" .. outputdir .. "/Game",
            "{COPYFILE} %{cfg.buildtarget.relpath} %{wks.location}Binaries/" .. outputdir .. "/Game",
            "{COPYFILE} %{wks.location}%{prj.name}/ThirdParty/SDL/lib/x64/SDL3.dll %{wks.location}Binaries/" .. outputdir .. "/Game"
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

        filter {}





project "Game"
    location "Game"
    kind "ConsoleApp"
    language "C++"

    targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
    objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")
    
    files{
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp"
    }

    links{
        "FireboxEngine"
    }

    includedirs{
        "FireboxEngine/ThirdParty/spdlog/include",
        "FireboxEngine/ThirdParty/SDL/include",
        "FireboxEngine/ThirdParty/GLM",
        "FireboxEngine/ThirdParty/ImGui",
        "FireboxEngine/Source"
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

        filter {}


project "FireboxEditor"
    location "FireboxEditor"
    kind "ConsoleApp"
    language "C++"

    targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
    objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")
    
    files{
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp"
    }

    links{
        "FireboxEngine",
        "SDL3",
        "opengl32.lib",
        "Glad",
        "imgui"
    }

    libdirs{
        "FireboxEngine/ThirdParty/SDL/lib/x64"
    }

    includedirs{
        "FireboxEngine/ThirdParty/spdlog/include",
        "FireboxEngine/ThirdParty/SDL/include",
        "FireboxEngine/ThirdParty/GLM",
        "FireboxEngine/ThirdParty/ImGui",
        "FireboxEngine/Source",
        "%{prj.name}/Source"
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
        
        filter {}