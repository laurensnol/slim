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
    m_properties = WindowProperties(title, width, height, vsync);
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

    m_window = glfwCreateWindow(m_properties.width, m_properties.height, m_properties.title.c_str(), NULL, NULL);

    if (!m_window)
      SLIM_ASSERT(false, "Failed to create GLFW window")

    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow *window, int width, int height)
    {
      glViewport(0, 0, width, height);

      WindowProperties &properties = *(WindowProperties*)glfwGetWindowUserPointer(window);
      properties.width = width;
      properties.height = height;
    });

    glfwSetWindowUserPointer(m_window, &m_properties);
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(m_properties.vsync ? 1 : 0);

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0)
      SLIM_ASSERT(false, "Failed to initialize OpenGL context")

    int framebufferWidth, framebufferHeight;
    glfwGetFramebufferSize(m_window, &framebufferWidth, &framebufferHeight);
    glViewport(0, 0, framebufferWidth, framebufferHeight);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    spdlog::info("Loaded OpenGL {}.{}", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));
  }

  void MacOSWindow::destroy()
  {
    glfwDestroyWindow(m_window);
    glfwTerminate();
  }

  bool MacOSWindow::shouldClose()
  {
    return glfwWindowShouldClose(m_window);
  }

  void MacOSWindow::update()
  {
    glfwPollEvents();
    glfwSwapBuffers(m_window);
  }

  void *MacOSWindow::getNative() const
  {
    return m_window;
  }

  WindowProperties MacOSWindow::getProperties() const
  {
    return m_properties;
  }

  glm::vec2 MacOSWindow::getDimensions() const
  {
    return glm::vec2{m_properties.width, m_properties.height};
  }

  void MacOSWindow::setWidth(float width)
  {
    m_properties.width = width;
    glViewport(0, 0, m_properties.width, m_properties.height);
  }
 
  void MacOSWindow::setHeight(float height)
  {
    m_properties.height = height;
    glViewport(0, 0, m_properties.width, m_properties.height);
  }

  bool MacOSWindow::getVsync() const
  {
    return m_properties.vsync;
  }

  void MacOSWindow::setVsync(bool value)
  {
    m_properties.vsync = value;
    glfwSwapInterval(m_properties.vsync ? 1 : 0);
  }
}