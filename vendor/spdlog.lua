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

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"