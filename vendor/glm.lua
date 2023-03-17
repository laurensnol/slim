project "glm"
    kind "StaticLib"
    language "C"
    staticruntime "On"

    targetdir "../bin/%{prj.name}"
    objdir "../obj/%{prj.name}"

    files { "glm/glm/**" }

    filter "system:windows"
        systemversion "latest"

        defines { "_CRT_SECURE_NO_WARNINGS" }

    filter "system:linux"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

	  filter "configurations:Release"
		    runtime "Release"
		    optimize "on"