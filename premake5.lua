include "vendor/premake-plugins/export-compile-commands.lua"

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
IncludeDir["PhysX"] = "ThirdParty/PhysX"
IncludeDir["PhysXInc"] = "ThirdParty/PhysX/physx/include"
IncludeDir["abseil"] = "ThirdParty/abseil-cpp"

include "ThirdParty/Glad"
include "ThirdParty/ImGui"
include "ThirdParty/ImGuizmo"
include "ThirdParty/assimp"
include "ThirdParty/PhysX"

project "FireboxRuntime"
    location "Engine/Source/Runtime"
    language "C++"

    targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
    objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")
    
    files{
        "Engine/Source/Runtime/**.h",
        "Engine/Source/Runtime/**.cpp"
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
        "%{IncludeDir.PhysX}",
        "%{IncludeDir.PhysXInc}",
        "%{IncludeDir.abseil}",
        "Engine/Source/Runtime"
    }

    removefiles{
        "ThirdParty/GLM/glm/glm.cppm"
    }

    links{
        "SDL3",
        "Glad",
        "imgui",
        "ImGuizmo",
        "assimp",
        "PhysX"
        }

    defines{
        "GLM_FORCE_DEPTH_ZERO_TO_ONE",
        "PX_PHYSX_STATIC_LIB"
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
        cppdialect "C++20"
        systemversion "latest"
        defines{ "FIREBOX_PLATFORM_WIN64", "FIREBOX_BUILD_DLL" }
        links { "opengl32.lib", "imm32" }
        libdirs{ "ThirdParty/SDL/lib/x64" }
        buildoptions "/utf-8"

    filter "system:linux"
        cppdialect "C++20"
        defines{ "FIREBOX_PLATFORM_LINUX", "FIREBOX_BUILD_DLL" }
        links { "GL", "dl", "pthread", "X11" }
        libdirs{ "ThirdParty/SDL/lib/linux-x64" }
        pic "On"

    filter "configurations:Debug or Release"
    kind "SharedLib"
    defines "FIREBOX_BUILD_DLL"
    postbuildcommands{
        "{MKDIR} %{wks.location}/Binaries/" .. outputdir .. "/FireboxEditor",
        "{COPY} %{cfg.buildtarget.relpath} %{wks.location}/Binaries/" .. outputdir .. "/FireboxEditor",

        "{MKDIR} %{wks.location}/Binaries/" .. outputdir .. "/Projects/SampleGame",
        "{COPY} %{cfg.buildtarget.relpath} %{wks.location}/Binaries/" .. outputdir .. "/Projects/SampleGame"
    }

    filter "configurations:Shipping"
        kind "StaticLib"
        defines "FIREBOX_STATIC"
        postbuildcommands{
            "{MKDIR} %{wks.location}/Binaries/" .. outputdir .. "/FireboxEditor",
            "{MKDIR} %{wks.location}/Binaries/" .. outputdir .. "/Projects/SampleGame"
        }

    filter { "configurations:Debug or Release or Shipping", "system:windows" }
        postbuildcommands{
            "{COPY} %{wks.location}/ThirdParty/SDL/lib/x64/SDL3.dll %{wks.location}/Binaries/" .. outputdir .. "/FireboxEditor",
            "{COPY} %{wks.location}/ThirdParty/SDL/lib/x64/SDL3.dll %{wks.location}/Binaries/" .. outputdir .. "/Projects/SampleGame"
        }

    filter { "configurations:Debug or Release or Shipping", "system:linux" }
        postbuildcommands{
            "{COPY} %{wks.location}/ThirdParty/SDL/lib/linux-x64/libSDL3.so* %{wks.location}/Binaries/" .. outputdir .. "/FireboxEditor",
            "{COPY} %{wks.location}/ThirdParty/SDL/lib/linux-x64/libSDL3.so* %{wks.location}/Binaries/" .. outputdir .. "/Projects/SampleGame"
        }

    filter "configurations:Debug"
        defines {
          "FIREBOX_DEBUG",
          " _DEBUG"  
        } 
        symbols "On"
        staticruntime "Off"

    filter "configurations:Release"
        defines {
            "FIREBOX_RELEASE",
            "NDEBUG"
        }
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
        "ThirdParty/PhysX",
        "%{IncludeDir.PhysXInc}",
        "ThirdParty/abseil-cpp",
        "Engine/Source/Runtime"
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
        cppdialect "C++20"
        systemversion "latest"

        defines{
            "FIREBOX_PLATFORM_WIN64"
        }

        links {
            "imm32"
        }

        filter "configurations:Debug"
            defines {
                "FIREBOX_DEBUG",
                " _DEBUG"  
            }
            symbols "On"
            staticruntime "Off"
            kind "ConsoleApp"

        filter "configurations:Release"
            defines {
                "FIREBOX_RELEASE",
                "NDEBUG"
            }
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

    filter "system:linux"
        cppdialect "C++20"

        defines{
            "FIREBOX_PLATFORM_LINUX"
        }

        links {
            "SDL3",
            "dl",
            "pthread"
        }

        libdirs{
            "ThirdParty/SDL/lib/linux-x64"
        }

        filter { "system:linux", "configurations:Debug" }
            defines {
                "FIREBOX_DEBUG",
                "_DEBUG"
            }
            symbols "On"
            staticruntime "Off"
            kind "ConsoleApp"

        filter { "system:linux", "configurations:Release" }
            defines {
                "FIREBOX_RELEASE",
                "NDEBUG"
            }
            optimize "On"
            staticruntime "Off"
            kind "ConsoleApp"

        filter { "system:linux", "configurations:Shipping" }
            defines "FIREBOX_SHIPPING"
            optimize "On"
            staticruntime "On"
            kind "ConsoleApp"

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
        "Glad",
        "imgui",
        "ImGuizmo",
        "PhysX"
    }

    dependson { "SampleGame" }

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
        "ThirdParty/PhysX",
        "%{IncludeDir.PhysXInc}",
        "ThirdParty/abseil-cpp",
        "Engine/Source/Runtime",
        "%{IncludeDir.Glad}",
        "Engine/Source/Editor"
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
        cppdialect "C++20"
        systemversion "latest"

        defines{
            "FIREBOX_PLATFORM_WIN64"
        }

        links {
            "SDL3",
            "opengl32.lib",
            "imm32"
        }

        libdirs{
            "ThirdParty/SDL/lib/x64"
        }

        filter "configurations:Debug"
            defines {
                "FIREBOX_DEBUG",
                "_DEBUG"
            }
            symbols "On"
            staticruntime "Off"

        filter "configurations:Release"
            defines {
                "FIREBOX_RELEASE",
                "NDEBUG"
            }
            optimize "On"
            staticruntime "Off"

        filter "configurations:Shipping"
            defines "FIREBOX_SHIPPING"
            optimize "On"
            staticruntime "On"

        filter {"system:windows"}  
            buildoptions "/utf-8"
        
        filter {}

    filter "system:linux"
        cppdialect "C++20"

        defines{
            "FIREBOX_PLATFORM_LINUX"
        }

        links {
            "SDL3",
            "GL",
            "dl",
            "pthread",
            "X11"
        }

        libdirs{
            "ThirdParty/SDL/lib/linux-x64"
        }

        filter { "system:linux", "configurations:Debug" }
            defines {
                "FIREBOX_DEBUG",
                "_DEBUG"
            }
            symbols "On"
            staticruntime "Off"

        filter { "system:linux", "configurations:Release" }
            defines {
                "FIREBOX_RELEASE",
                "NDEBUG"
            }
            optimize "On"
            staticruntime "Off"

        filter { "system:linux", "configurations:Shipping" }
            defines "FIREBOX_SHIPPING"
            optimize "On"
            staticruntime "On"

        filter {}