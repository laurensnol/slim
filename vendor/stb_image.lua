project "stb_image"
    kind "StaticLib"
    language "C"
    staticruntime "On"

    targetdir "../bin/%{prj.name}"
    objdir "../obj/%{prj.name}"

    files
    {
        "stb_image/stb_image.h",
        "stb_image/stb_image.cpp"
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