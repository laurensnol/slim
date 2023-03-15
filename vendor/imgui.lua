project "imgui"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "On"

    targetdir "../bin/%{prj.name}"
    objdir "../obj/%{prj.name}"

    defines { "IMGUI_IMPL_OPENGL_LOADER_GLAD" }

    files
    {
        "imgui/*.cpp",
        "imgui/backends/imgui_impl_glfw.cpp",
		    "imgui/backends/imgui_impl_opengl3.cpp"
    }

    includedirs { "imgui" }

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
