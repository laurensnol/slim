#include "slim/platform/desktop_window.hpp"

// IWYU pragma: no_include "glm/detail/qualifier.hpp"
// IWYU pragma: no_include "glm/detail/type_vec2.inl"

#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <cassert>
#include <cstdint>
#include <glm/ext/vector_int2.hpp>
#include <iostream>
#include <string>
#include <utility>

#include "slim/events/event_bus.hpp"
#include "slim/events/window_events.hpp"

namespace slim {
DesktopWindow::DesktopWindow(std::string title, uint16_t width, uint16_t height,
                             bool vsync, bool focused, bool minimized) noexcept
    : properties_{std::move(title), width, height, vsync, focused, minimized} {
  assert(!(focused && minimized));  // A window may not be focused and minimized

  assert(glfwInit());

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

  if (!properties_.focused) {
    glfwWindowHint(GLFW_FOCUSED, GLFW_FALSE);
  }

  if (properties_.minimized) {
    glfwWindowHint(GLFW_ICONIFIED, GLFW_TRUE);
  }

  window_ = glfwCreateWindow(properties_.width, properties_.height,
                             properties_.title.c_str(), nullptr, nullptr);
  assert(window_);

  glfwSetWindowUserPointer(window_, &properties_);
  glfwSetWindowCloseCallback(window_, glfwCloseCallback);
  glfwSetFramebufferSizeCallback(window_, glfwFramebufferSizeCallback);
  glfwSetWindowFocusCallback(window_, glfwWindowFocusCallback);
  glfwSetWindowIconifyCallback(window_, glfwWindowIconifyCallback);
  glfwSetKeyCallback(window_, glfwKeyCallback);
  glfwSetMouseButtonCallback(window_, glfwMouseButtonCallback);
  glfwSetCursorPosCallback(window_, glfwCursorPosCallback);

  glfwMakeContextCurrent(window_);
  gladLoadGL(glfwGetProcAddress);
  glfwSwapInterval(properties_.vsync ? 1 : 0);
}

DesktopWindow::~DesktopWindow() noexcept {
  glfwDestroyWindow(window_);
  glfwTerminate();
}

auto DesktopWindow::update() const noexcept -> void {
  glfwSwapBuffers(window_);
  glfwPollEvents();
}

auto DesktopWindow::close() const noexcept -> void {
  glfwSetWindowShouldClose(window_, GLFW_TRUE);
}

auto DesktopWindow::isOpen() const noexcept -> bool {
  return glfwWindowShouldClose(window_) == 0;
}

auto DesktopWindow::setTitle(const std::string &title) noexcept -> void {
  properties_.title = title;
  glfwSetWindowTitle(window_, properties_.title.c_str());
}

auto DesktopWindow::getTitle() const noexcept -> const std::string & {
  return properties_.title;
}

auto DesktopWindow::setDimensions(const glm::ivec2 &dimensions) noexcept
    -> void {
  glfwSetWindowSize(window_, dimensions.x, dimensions.y);  // NOLINT
}

auto DesktopWindow::getDimensions() const noexcept -> glm::ivec2 {
  return {properties_.width, properties_.height};
}

auto DesktopWindow::setWidth(uint16_t width) noexcept -> void {
  glfwSetWindowSize(window_, width, properties_.height);
}

auto DesktopWindow::getWidth() const noexcept -> uint16_t {
  return properties_.width;
}

auto DesktopWindow::setHeight(uint16_t height) noexcept -> void {
  glfwSetWindowSize(window_, properties_.width, height);
}

auto DesktopWindow::getHeight() const noexcept -> uint16_t {
  return properties_.height;
}

auto DesktopWindow::setVsync(bool value) noexcept -> void {
  properties_.vsync = value;
  glfwSwapInterval(properties_.vsync ? 1 : 0);
}

auto DesktopWindow::getVsync() const noexcept -> bool {
  return properties_.vsync;
}

auto DesktopWindow::setFocus(bool value) noexcept -> void {
  properties_.focused = value;
  glfwSetWindowAttrib(window_, GLFW_FOCUSED,
                      static_cast<int>(properties_.focused));
}

auto DesktopWindow::isFocused() const noexcept -> bool {
  return properties_.focused;
}

auto DesktopWindow::setMinimize(bool value) noexcept -> void {
  properties_.minimized = value;
  if (properties_.minimized) {
    glfwIconifyWindow(window_);
  } else {
    glfwRestoreWindow(window_);
  }
}

auto DesktopWindow::isMinimized() const noexcept -> bool {
  return properties_.minimized;
}

auto DesktopWindow::glfwCloseCallback(GLFWwindow * /*window*/) noexcept
    -> void {
  EventBus::publish<WindowCloseEvent>();
}

auto DesktopWindow::glfwFramebufferSizeCallback(GLFWwindow *window, int width,
                                                int height) noexcept -> void {
  auto *props =
      static_cast<WindowProperties *>(glfwGetWindowUserPointer(window));
  props->width = static_cast<uint16_t>(width);
  props->height = static_cast<uint16_t>(height);

  auto event = WindowResizeEvent({width, height});
  EventBus::publish<WindowResizeEvent>(event);
}

auto DesktopWindow::glfwWindowFocusCallback(GLFWwindow *window,
                                            int focused) noexcept -> void {
  auto *props =
      static_cast<WindowProperties *>(glfwGetWindowUserPointer(window));
  props->focused = (focused != 0);

  EventBus::publish<WindowFocusEvent>(focused);
}

auto DesktopWindow::glfwWindowIconifyCallback(GLFWwindow *window,
                                              int iconified) noexcept -> void {
  auto *props =
      static_cast<WindowProperties *>(glfwGetWindowUserPointer(window));
  props->minimized = (iconified != 0);

  EventBus::publish<WindowMinimizeEvent>(iconified);
}

auto DesktopWindow::glfwKeyCallback(GLFWwindow * /*window*/, int key,
                                    int scancode, int action, int mods) noexcept
    -> void {
  std::cout << "GLFW: Key: " << key << ", " << scancode << ", " << action
            << ", " << mods << "\n";
  // TODO(laurensnol)
}

auto DesktopWindow::glfwMouseButtonCallback(GLFWwindow * /*window*/, int button,
                                            int action, int mods) noexcept
    -> void {
  std::cout << "GLFW: Mouse: " << button << ", " << action << ", " << mods
            << "\n";
  // TODO(laurensnol)
}

auto DesktopWindow::glfwCursorPosCallback(GLFWwindow * /*window*/, double xpos,
                                          double ypos) noexcept -> void {
  std::cout << "GLFW: Cursor: " << xpos << ", " << ypos << "\n";
  // TODO(laurensnol)
}
}  // namespace slim
