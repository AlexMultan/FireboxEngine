workspace "FireboxEngine"
    architecture "x64"

    configurations{
        "Debug",
        "Release",
        "Shipping"
    }

outputdir = "%{cfg.buildcfg}-x64"

IncludeDir = {}
IncludeDir["SDL"] = "ThirdParty/SDL/include"
IncludeDir["Glad"] = "ThirdParty/Glad/include"
IncludeDir["imgui"] = "ThirdParty/ImGui"
IncludeDir["glm"] = "ThirdParty/GLM"
IncludeDir["stb"] = "ThirdParty/stb"
IncludeDir["entt"] = "ThirdParty/entt/include"
IncludeDir["assimp"] = "ThirdParty/assimp/include"
IncludeDir["ImGuizmo"] = "ThirdParty/ImGuizmo/src"
IncludeDir["json"] = "ThirdParty/json/include"

include "ThirdParty/Glad"
include "ThirdParty/ImGui"
include "ThirdParty/ImGuizmo"
include "ThirdParty/assimp"

project "Engine"
    location "Engine"
    language "C++"

    targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
    objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")
    
    files{
        "%{prj.name}/Source/**/**.h",
        "%{prj.name}/Source/**/**.cpp",
    }

    includedirs{
        "ThirdParty/spdlog/include",
        "%{IncludeDir.SDL}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.imgui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.entt}",
        "%{IncludeDir.stb}",
        "%{IncludeDir.assimp}",
        "%{IncludeDir.ImGuizmo}",
        "%{IncludeDir.json}",
        "%{prj.name}/Source"
    }

    removefiles{
        "ThirdParty/GLM/glm/glm.cppm"
    }

    links{
        "SDL3",
        "opengl32.lib",
        "Glad",
        "imgui",
        "ImGuizmo",
        "assimp"
        }

    defines{
        "GLM_FORCE_DEPTH_ZERO_TO_ONE"
    }

    libdirs{
        "ThirdParty/SDL/lib/x64"
    }

    filter "system:windows"
        cppdialect "C++20"
        systemversion "latest"
        defines{ "FIREBOX_PLATFORM_WIN64", "FIREBOX_BUILD_DLL" }
        links { "imm32" }
        buildoptions "/utf-8"

    filter "configurations:Debug or Release"
        kind "SharedLib"
        defines "FIREBOX_BUILD_DLL"
        postbuildcommands{
            "{MKDIR} %{wks.location}Binaries/" .. outputdir .. "/Editor",
            "{COPY} %{cfg.buildtarget.relpath} %{wks.location}Binaries/" .. outputdir .. "/Editor",
            "{COPY} %{wks.location}ThirdParty/SDL/lib/x64/SDL3.dll %{wks.location}Binaries/" .. outputdir .. "/Editor",

            "{MKDIR} %{wks.location}Binaries/" .. outputdir .. "/Projects/SampleGame",
            "{COPY} %{cfg.buildtarget.relpath} %{wks.location}Binaries/" .. outputdir .. "/Projects/SampleGame",
            "{COPY} %{wks.location}ThirdParty/SDL/lib/x64/SDL3.dll %{wks.location}Binaries/" .. outputdir .. "/Projects/SampleGame"
        }

    filter "configurations:Shipping"
        kind "StaticLib"
        defines "FIREBOX_STATIC"
        postbuildcommands{
            "{MKDIR} %{wks.location}Binaries/" .. outputdir .. "/Editor",
            "{COPY} %{wks.location}ThirdParty/SDL/lib/x64/SDL3.dll %{wks.location}Binaries/" .. outputdir .. "/Editor",
            "{MKDIR} %{wks.location}Binaries/" .. outputdir .. "/Projects/SampleGame",
            "{COPY} %{wks.location}ThirdParty/SDL/lib/x64/SDL3.dll %{wks.location}Binaries/" .. outputdir .. "/Projects/SampleGame"
        }

    filter "configurations:Debug"
        defines "FIREBOX_DEBUG"
        symbols "On"
        staticruntime "Off"

    filter "configurations:Release"
        defines "FIREBOX_RELEASE"
        optimize "On"
        staticruntime "Off"

    filter "configurations:Shipping"
        defines "FIREBOX_SHIPPING"
        optimize "On"
        staticruntime "On"

    filter {}




project "SampleGame"
    location "Projects/SampleGame"
    kind "ConsoleApp"
    language "C++"

    targetdir ("Binaries/" .. outputdir .. "/Projects/%{prj.name}")
    objdir ("Intermediate/" .. outputdir .. "/Projects/%{prj.name}")
    
    files{
        "Projects/%{prj.name}/Source/**.h",
        "Projects/%{prj.name}/Source/**.cpp",
    }

    links{
        "Engine"
    }

    includedirs{
        "ThirdParty/spdlog/include",
        "ThirdParty/SDL/include",
        "ThirdParty/GLM",
        "ThirdParty/ImGui",
        "ThirdParty/stb",
        "ThirdParty/entt/include",
        "ThirdParty/ImGuizmo/src",
        "ThirdParty/assimp/include",
        "ThirdParty/json/include",
        "Engine/Source"
    }

    filter "system:windows"
        cppdialect "C++20"
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
            staticruntime "Off"
            kind "ConsoleApp"

        filter "configurations:Release"
            defines "FIREBOX_RELEASE"
            optimize "On"
            staticruntime "Off"
            kind "ConsoleApp"

        filter "configurations:Shipping"
            defines "FIREBOX_SHIPPING"
            optimize "On"
            staticruntime "On"
            kind "ConsoleApp"

        filter {"system:windows"}  
            buildoptions "/utf-8"

        filter {}


project "Editor"
    location "Editor"
    kind "ConsoleApp"
    language "C++"

    targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
    objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")
    
    files{
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp",
    }

    links{
        "Engine",
        "SDL3",
        "opengl32.lib",
        "Glad",
        "imgui",
        "ImGuizmo"
    }

    dependson { "SampleGame" }

    libdirs{
        "ThirdParty/SDL/lib/x64"
    }

    includedirs{
        "ThirdParty/spdlog/include",
        "ThirdParty/SDL/include",
        "ThirdParty/GLM",
        "ThirdParty/ImGui",
        "ThirdParty/stb",
        "ThirdParty/entt/include",
        "ThirdParty/assimp/include",
        "ThirdParty/ImGuizmo/src",
        "ThirdParty/json/include",
        "Engine/Source",
        "%{IncludeDir.Glad}",
        "%{prj.name}/Source"
    }

    filter "system:windows"
        cppdialect "C++20"
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
            staticruntime "Off"

        filter "configurations:Release"
            defines "FIREBOX_RELEASE"
            optimize "On"
            staticruntime "Off"

        filter "configurations:Shipping"
            defines "FIREBOX_SHIPPING"
            optimize "On"
            staticruntime "On"

        filter {"system:windows"}  
            buildoptions "/utf-8"
        
        filter {}