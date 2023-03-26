#include "platform/MacOS/MacOSWindow.h"

#include "core/base.h"
#include <spdlog/spdlog.h>

namespace slim
{
  static void GLFWErrorCallback(int error, const char* description)
  {
    spdlog::error("GLFW Error {}: {}", error, description);
  }

  MacOSWindow::MacOSWindow(std::string_view title, uint16_t width, uint16_t height, bool vsync)
  {
    _properties = WindowProperties(title, width, height, vsync);
    init();
  }

  MacOSWindow::~MacOSWindow()
  {
    destroy();
  }
 
  void MacOSWindow::init()
  {
    glfwSetErrorCallback(GLFWErrorCallback);

    if (!glfwInit())
      SLIM_ASSERT(false, "Failed to initialize GLFW")

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef SLIM_PLATFORM_MACOS
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    _window = glfwCreateWindow(_properties.width, _properties.height, _properties.title.c_str(), NULL, NULL);

    if (!_window)
      SLIM_ASSERT(false, "Failed to create GLFW window")

    glfwSetFramebufferSizeCallback(_window, [](GLFWwindow *window, int width, int height)
    {
      glViewport(0, 0, width, height);

      WindowProperties &properties = *(WindowProperties*)glfwGetWindowUserPointer(window);
      properties.width = width;
      properties.height = height;
    });

    glfwSetWindowUserPointer(_window, &_properties);
    glfwMakeContextCurrent(_window);
    glfwSwapInterval(_properties.vsync ? 1 : 0);

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0)
      SLIM_ASSERT(false, "Failed to initialize OpenGL context")

    int framebufferWidth, framebufferHeight;
    glfwGetFramebufferSize(_window, &framebufferWidth, &framebufferHeight);
    glViewport(0, 0, framebufferWidth, framebufferHeight);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

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

  void *MacOSWindow::getNative() const
  {
    return _window;
  }

  WindowProperties MacOSWindow::getProperties() const
  {
    return _properties;
  }

  glm::vec2 MacOSWindow::getDimensions() const
  {
    return glm::vec2{_properties.width, _properties.height};
  }

  void MacOSWindow::setWidth(float width)
  {
    _properties.width = width;
    glViewport(0, 0, _properties.width, _properties.height);
  }
 
  void MacOSWindow::setHeight(float height)
  {
    _properties.height = height;
    glViewport(0, 0, _properties.width, _properties.height);
  }

  bool MacOSWindow::getVsync() const
  {
    return _properties.vsync;
  }

  void MacOSWindow::setVsync(bool value)
  {
    _properties.vsync = value;
    glfwSwapInterval(_properties.vsync ? 1 : 0);
  }
}