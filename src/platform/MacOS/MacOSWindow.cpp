#include "platform/MacOS/MacOSWindow.h"

namespace slim
{
  static void GLFWErrorCallback(int error, const char* description)
  {
    spdlog::error("GLFW Error {}: {}", error, description);
    exit(-1);
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
    {
      spdlog::error("Failed to initialize GLFW");
      assert(false);
    }

    glfwSetErrorCallback(GLFWErrorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef SLIM_PLATFORM_MACOS
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    _window = glfwCreateWindow(_properties.width, _properties.height, _properties.title.c_str(), NULL, NULL);

    if (_window == NULL)
    {
      spdlog::error("Failed to create GLFW window");
      assert(false);
    }

    glfwSetWindowUserPointer(_window, &_properties);
    glfwMakeContextCurrent(_window);

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0)
    {
      spdlog::critical("Failed to initialize OpenGL context");
      assert(false);
    }

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