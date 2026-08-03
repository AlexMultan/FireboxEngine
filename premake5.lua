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
IncludeDir["VulkanSDK"] = "ThirdParty/VulkanSDK/Include"

LibDir = {}
LibDir["VulkanSDK"] = "ThirdParty/VulkanSDK/Lib"

include "ThirdParty/Glad"
include "ThirdParty/ImGui"
include "ThirdParty/ImGuizmo"
include "ThirdParty/assimp"

project "FireboxRuntime"
    location "Engine/Source/Runtime"
    language "C++"

    targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
    objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")
    
    files{
        "Engine/Source/Runtime/**.h",
        "Engine/Source/Runtime/**.cpp",
        "Resources/EngineContent/Shaders/GLSL/**.vert",
        "Resources/EngineContent/Shaders/GLSL/**.frag",
        "Resources/EngineContent/Shaders/GLSL/**.geom",
        "Resources/EngineContent/Shaders/GLSL/**.comp"
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
        "%{IncludeDir.VulkanSDK}",
        "Engine/Source/Runtime"
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
        "assimp",
        "vulkan-1"
        }

    defines{
        "GLM_FORCE_DEPTH_ZERO_TO_ONE"
    }

    libdirs{
        "ThirdParty/SDL/lib/x64",
        "%{LibDir.VulkanSDK}"
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
            "{MKDIR} %{wks.location}Binaries/" .. outputdir .. "/FireboxEditor",
            "{COPY} %{cfg.buildtarget.relpath} %{wks.location}Binaries/" .. outputdir .. "/FireboxEditor",
            "{COPY} %{wks.location}ThirdParty/SDL/lib/x64/SDL3.dll %{wks.location}Binaries/" .. outputdir .. "/FireboxEditor",

            "{MKDIR} %{wks.location}Binaries/" .. outputdir .. "/Projects/SampleGame",
            "{COPY} %{cfg.buildtarget.relpath} %{wks.location}Binaries/" .. outputdir .. "/Projects/SampleGame",
            "{COPY} %{wks.location}ThirdParty/SDL/lib/x64/SDL3.dll %{wks.location}Binaries/" .. outputdir .. "/Projects/SampleGame"
        }

    filter "configurations:Shipping"
        kind "StaticLib"
        defines "FIREBOX_STATIC"
        postbuildcommands{
            "{MKDIR} %{wks.location}Binaries/" .. outputdir .. "/FireboxEditor",
            "{COPY} %{wks.location}ThirdParty/SDL/lib/x64/SDL3.dll %{wks.location}Binaries/" .. outputdir .. "/FireboxEditor",
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
        "FireboxRuntime"
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
        "Engine/Source/Runtime"
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


project "FireboxEditor"
    location "Engine/Source/Editor"
    kind "ConsoleApp"
    language "C++"

    targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
    objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")
    
    files{
        "Engine/Source/Editor/**.h",
        "Engine/Source/Editor/**.cpp",
    }

    links{
        "FireboxRuntime",
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
        "Engine/Source/Runtime",
        "%{IncludeDir.Glad}",
        "Engine/Source/Editor"
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