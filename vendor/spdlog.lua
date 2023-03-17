project "spdlog"
    kind "StaticLib"
    language "C++"
    staticruntime "On"

    targetdir "../bin/%{prj.name}"
    objdir "../obj/%{prj.name}"

    files
    {
        "spdlog/src/spdlog.cpp",
        "spdlog/src/stdout_sinks.cpp",
        "spdlog/src/color_sinks.cpp",
        "spdlog/src/file_sinks.cpp",
        "spdlog/src/async.cpp",
        "spdlog/src/cfg.cpp",
        "spdlog/src/bundled_fmtlib_format.cpp"
    }

    filter "system:windows"
        systemversion "latest"

        defines { "_CRT_SECURE_NO_WARNINGS" }

    filter "system:linux"
        pic "On"

        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"