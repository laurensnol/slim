project "GLFW"
    kind "StaticLib"
    language "C"
    staticruntime "On"

    targetdir "../bin/%{prj.name}"
    objdir "../obj/%{prj.name}"

    files
    {
        "glfw/src/glfw_config.h",
        "glfw/include/GLFW/glfw3.h",
        "glfw/include/GLFW/glfw3native.h",

        "glfw/src/context.c",
        "glfw/src/init.c",
        "glfw/src/input.c",
        "glfw/src/monitor.c",
        "glfw/src/vulkan.c",
        "glfw/src/window.c"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "_CRT_SECURE_NO_WARNINGS",
            "_GLFW_WIN32"
        }

        files
        {
            "glfw/src/win32_platform.h",
            "glfw/src/win32_joystick.h",
            "glfw/src/wgl_context.h",
            "glfw/src/egl_context.h",
            "glfw/src/osmesa_context.h",

            "glfw/src/win32_init.c",
            "glfw/src/win32_joystick.c",
            "glfw/src/win32_monitor.c",
            "glfw/src/win32_time.c",
            "glfw/src/win32_thread.c",
            "glfw/src/win32_window.c",
            "glfw/src/wgl_context.c",
            "glfw/src/egl_context.c",
            "glfw/src/osmesa_context.c"
        }

    filter "system:linux"
        pic "On"

        systemversion "latest"

        defines { "_GLFW_X11" }

        files
        {
            "glfw/src/x11_platform.h",
            "glfw/src/xkb_unicode.h",
            "glfw/src/posix_time.h",
            "glfw/src/posix_thread.h",
            "glfw/src/glx_context.h",
            "glfw/src/egl_context.h",
            "glfw/src/osmesa_context.h",

            "glfw/src/x11_init.c",
            "glfw/src/x11_monitor.c",
            "glfw/src/x11_window.c",
            "glfw/src/xkb_unicode.c",
            "glfw/src/posix_time.c",
            "glfw/src/posix_thread.c",
            "glfw/src/glx_context.c",
            "glfw/src/egl_context.c",
            "glfw/src/osmesa_context.c"
        }

    filter "system:macosx"
        defines { "_GLFW_COCOA" }

        files
        {
            "glfw/src/cocoa_platform.h",
            "glfw/src/cocoa_joystick.h",
            "glfw/src/posix_thread.h",
            "glfw/src/nsgl_context.h",
            "glfw/src/egl_context.h",
            "glfw/src/osmesa_context.h",
            
            "glfw/src/cocoa_init.m",
            "glfw/src/cocoa_joystick.m",
            "glfw/src/cocoa_monitor.m",
            "glfw/src/cocoa_window.m",
            "glfw/src/cocoa_time.c",
            "glfw/src/posix_thread.c",
            "glfw/src/nsgl_context.m",
            "glfw/src/egl_context.c",
            "glfw/src/osmesa_context.c"
        }

    filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"