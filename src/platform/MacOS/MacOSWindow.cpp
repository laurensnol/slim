#include "platform/MacOS/MacOSWindow.h"

#include "core/base.h"
#include <spdlog/spdlog.h>

namespace slim
{
  static void GLFWErrorCallback(int error, const char* description)
  {
    spdlog::error("GLFW Error {}: {}", error, description);
  }

  MacOSWindow::MacOSWindow(const WindowProperties &properties)
  {
    init(properties);
  }

  MacOSWindow::~MacOSWindow()
  {
    destroy();
  }
 
  void MacOSWindow::init(const WindowProperties &properties)
  {
    _properties = std::move(properties);

    if (!glfwInit())
      SLIM_ASSERT(false, "Failed to initialize GLFW")

    glfwSetErrorCallback(GLFWErrorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef SLIM_PLATFORM_MACOS
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    _window = glfwCreateWindow(_properties.width, _properties.height, _properties.title.c_str(), NULL, NULL);

    if (_window == NULL)
      SLIM_ASSERT(false, "Failed to create GLFW window")

    glfwSetWindowUserPointer(_window, &_properties);
    glfwMakeContextCurrent(_window);

    glfwSetWindowSizeCallback(_window, [](GLFWwindow *window, int width, int height)
    {
      glViewport(0, 0, width, height);

      WindowProperties &properties = *(WindowProperties*)glfwGetWindowUserPointer(window);
      properties.width = width;
      properties.height = height;
    });

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0)
      SLIM_ASSERT(false, "Failed to initialize OpenGL context")

    spdlog::info("Loaded OpenGL {}.{}", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));
  }

  void MacOSWindow::destroy()
  {
    glfwDestroyWindow(_window);
    glfwTerminate();
  }

  bool MacOSWindow::shouldClose()
  {
    return glfwWindowShouldClose(_window);
  }

  void MacOSWindow::update()
  {
    glfwPollEvents();
    glfwSwapBuffers(_window);
  }

  void *MacOSWindow::getNative()
  {
    return _window;
  }

  WindowProperties MacOSWindow::getProperties()
  {
    return _properties;
  }
}