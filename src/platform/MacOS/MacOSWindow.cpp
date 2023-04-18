#include "platform/MacOS/MacOSWindow.h"

#include "core/base.h"
#include "events/window_events.h"
#include "events/event_bus.h"
#include "events/codes.h"
#include "events/key_events.h"
#include "events/mouse_events.h"
#include <spdlog/spdlog.h>
#include "MacOSWindow.h"

namespace slim
{
  MacOSWindow::MacOSWindow(std::string_view title, uint16_t width, uint16_t height, bool vsync)
  {
    m_properties = WindowProperties(title, width, height, vsync);
    init();
  }

  MacOSWindow::~MacOSWindow()
  {
    destroy();
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

  void* MacOSWindow::getNative() const
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

  void MacOSWindow::setDimensions(glm::vec2 size)
  {
    m_properties.width = size.x;
    m_properties.height = size.y;
    glViewport(0, 0, m_properties.width, m_properties.height);
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

  void MacOSWindow::init()
  {
    glfwSetErrorCallback(glfwErrorCallback);

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

    glfwSetWindowUserPointer(m_window, this);
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(m_properties.vsync ? 1 : 0);

    glfwSetWindowCloseCallback(m_window, glfwWindowCloseCallback);
    glfwSetFramebufferSizeCallback(m_window, glfwFramebufferSizeCallback);
    glfwSetWindowFocusCallback(m_window, glfwWindowFocusCallback);
    glfwSetWindowIconifyCallback(m_window, glfwWindowIconifyCallback);
    glfwSetKeyCallback(m_window, glfwKeyCallback);
    glfwSetMouseButtonCallback(m_window, glfwMouseButtonCallback);
    glfwSetCursorPosCallback(m_window, glfwCursorPosCallback);

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

  void MacOSWindow::glfwErrorCallback(int error, const char* description)
  {
    spdlog::error("GLFW Error {}: {}", error, description);
  }

  void MacOSWindow::glfwWindowCloseCallback(GLFWwindow* window)
  {
    glfwDestroyWindow(window);
    
    MacOSWindow* abstractWindow = (MacOSWindow*)glfwGetWindowUserPointer(window);
    WindowCloseEvent e{abstractWindow};
    EventBus::publish(e);
  }

  void MacOSWindow::glfwFramebufferSizeCallback(GLFWwindow* window, int width, int height)
  {
    glm::vec2 size{width, height};
    
    MacOSWindow* abstractWindow = (MacOSWindow*)glfwGetWindowUserPointer(window);
    abstractWindow->setDimensions(size);

    WindowResizeEvent e{abstractWindow, size};
    EventBus::publish(e);
  }

  void MacOSWindow::glfwWindowFocusCallback(GLFWwindow* window, int focused)
  {
    MacOSWindow* abstractWindow = (MacOSWindow*)glfwGetWindowUserPointer(window);
    WindowFocusEvent e{abstractWindow, focused ? true : false};
    EventBus::publish(e);
  }

  void MacOSWindow::glfwWindowIconifyCallback(GLFWwindow* window, int iconified)
  {
    MacOSWindow* abstractWindow = (MacOSWindow*)glfwGetWindowUserPointer(window);
    WindowMinimizeEvent e{abstractWindow, iconified ? true : false};
    EventBus::publish(e);
  }

  void MacOSWindow::glfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
  {
    Key code = static_cast<Key>(key);

    if (action == GLFW_PRESS)
    {
      KeyDownEvent e = KeyDownEvent(code, mods);
      EventBus::publish(e);
    }
    else if (action == GLFW_RELEASE)
    {
      KeyUpEvent e = KeyUpEvent(code, mods);
      EventBus::publish(e);
    }
  }

  void MacOSWindow::glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
  {
    spdlog::trace("Will send mouse");
    MouseButton code = static_cast<MouseButton>(button);

    if (action == GLFW_PRESS)
    {
      spdlog::trace("Will send mouse down");
      MouseDownEvent event(code, mods);
      EventBus::publish(event);
    }
    else if (action == GLFW_RELEASE)
    {
      spdlog::trace("Will send mouse release");
      MouseUpEvent event(code, mods);
      EventBus::publish(event);
    }
  }

  void MacOSWindow::glfwCursorPosCallback(GLFWwindow* window, double x, double y)
  {
    MouseMoveEvent event({x, y});
    EventBus::publish(event);
  }
}