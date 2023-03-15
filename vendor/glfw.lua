project "GLFW"
    kind "StaticLib"
    language "C"

    targetdir "../bin/%{prj.name}"
    objdir "../obj/%{prj.name}"

    files
    {
        "glfw/include/GLFW/glfw3.h",
        "glfw/include/GLFW/glfw3native.h",
        "glfw/src/context.c",
        "glfw/src/init.c",
        "glfw/src/input.c",
        "glfw/src/monitor.c",
        "glfw/src/vulkan.c",
        "glfw/src/window.c",
        "glfw/src/null_init.c",
		"glfw/src/null_monitor.c",
		"glfw/src/null_window.c",
		"glfw/src/null_joystick.c"
    }

    filter "system:windows"
        systemversion "latest"
        staticruntime "On"

        defines
        {
            "_GLFW_WIN32",
            "_CRT_SECURE_NO_WARNINGS"
        }

        files
        {
            "glfw/src/win32_init.c",
			"glfw/src/win32_joystick.c",
			"glfw/src/win32_monitor.c",
			"glfw/src/win32_time.c",
			"glfw/src/win32_thread.c",
			"glfw/src/win32_window.c",
			"glfw/src/wgl_context.c",
			"glfw/src/egl_context.c",
			"glfw/src/win32_module.c"
        }

    filter "system:linux"
        pic "On"

        systemversion "latest"
        staticruntime "On"

        defines { "_GLFW_X11" }

        files
        {
            "glfw/src/x11_init.c",
			"glfw/src/x11_monitor.c",
			"glfw/src/x11_window.c",
			"glfw/src/xkb_unicode.c",
			"glfw/src/posix_time.c",
			"glfw/src/posix_thread.c",
			"glfw/src/glx_context.c",
			"glfw/src/egl_context.c",
			"glfw/src/osmesa_context.c",
			"glfw/src/linux_joystick.c",
			"glfw/src/posix_module.c",
			"glfw/src/posix_poll.c"
        }

    filter "system:macosx"
        systemversion "latest"
        staticruntime "On"

        defines { "_GLFW_COCOA" }

        files
        {
            "glfw/src/cocoa_init.m",
            "glfw/src/cocoa_joystick.m",
            "glfw/src/cocoa_monitor.m",
            "glfw/src/cocoa_time.c",
            "glfw/src/cocoa_window.m",
            "glfw/src/nsgl_context.m",
            "glfw/src/posix_module.c",
			"glfw/src/posix_poll.c"
        }

    filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
