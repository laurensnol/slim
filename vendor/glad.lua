project "glad"
    kind "StaticLib"
    language "C"
    staticruntime "On"

    targetdir "../bin/%{prj.name}"
    objdir "../obj/%{prj.name}"

    files { "glad/src/gl.c" }

    includedirs { "glad/include" }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "_CRT_SECURE_NO_WARNINGS"
        }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
