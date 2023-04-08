-- premake5.lua
workspace "slim"
    startproject "slim"
    configurations
    {
        "Debug",
        "Release"
    }

project "slim"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    targetdir "bin/%{cfg.buildcfg}"
    objdir "obj/%{cfg.buildcfg}"

    --pchheader "slimpch.h"
    --pchsource "src/slimpch.cpp"

    files
    { 
        "src/**.h",
        "src/**.cpp"
    }
    
    includedirs
    {
        "src",
        "vendor/glfw/include",
        "vendor/glad/include",
        "vendor/spdlog/include",
        "vendor/imgui",
        "vendor/glm",
        "vendor/stb_image"
    }
    
    filter {}
        links
        {
            "glfw",
            "glad",
            "imgui",
            "stb_image"
        }

    filter "system:windows"
        defines { "SLIM_PLATFORM_WINDOWS" }

    filter "system:linux"
        defines { "SLIM_PLATFORM_LINUX" }

    filter "system:macosx"
        defines { "SLIM_PLATFORM_MACOS" }

        links
        {
            "/Library/Frameworks/Cocoa.framework",
            "/Library/Frameworks/OpenGL.framework",
            "/Library/Frameworks/IOKit.framework",
            "/Library/Frameworks/CoreVideo.framework"
        }
    
    filter "configurations:Debug"
        defines { "SLIM_DEBUG" }
        runtime "Debug"
        symbols "On"
    
    filter "configurations:Release"
        defines { "SLIM_RELEASE" }
        runtime "Release"
        optimize "On"

include "vendor/glfw.lua"
include "vendor/glad.lua"
include "vendor/spdlog.lua"
include "vendor/imgui.lua"
include "vendor/stb_image.lua"