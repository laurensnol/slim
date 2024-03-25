#include "slim/platform/desktop/desktop_window.hpp"

// IWYU pragma: no_include "glm/detail/qualifier.hpp"
// IWYU pragma: no_include "glm/detail/type_vec2.inl"
// IWYU pragma: no_include "spdlog/common.h"
// IWYU pragma: no_include <spdlog/fmt/fmt.h>

#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <spdlog/spdlog.h>

#include <cassert>
#include <cstdint>
#include <glm/ext/vector_int2.hpp>
#include <string>
#include <utility>

#include "slim/events/event_bus.hpp"
#include "slim/events/key_events.hpp"
#include "slim/events/mouse_events.hpp"
#include "slim/events/window_events.hpp"
#include "slim/input/codes.hpp"  // IWYU pragma: keep
#include "slim/ui/ui.hpp"

namespace slim {
DesktopWindow::DesktopWindow(std::string title, int32_t width, int32_t height,
                             bool vsync, bool focused, bool minimized) noexcept
    : properties_{std::move(title), width, height, vsync, focused, minimized} {
  assert(!(focused && minimized));  // A window may not be focused and minimized

  assert(glfwInit());

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef SLIM_PLATFORM_MACOS
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

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

  const int32_t version = gladLoadGL(glfwGetProcAddress);
  spdlog::info("Using OpenGL {}.{}", GLAD_VERSION_MAJOR(version),
               GLAD_VERSION_MINOR(version));

  glfwSwapInterval(properties_.vsync ? 1 : 0);

  UI::init(window_);
}

DesktopWindow::~DesktopWindow() noexcept {
  UI::shutdown();

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

auto DesktopWindow::setWidth(int32_t width) noexcept -> void {
  glfwSetWindowSize(window_, width, properties_.height);
}

auto DesktopWindow::getWidth() const noexcept -> int32_t {
  return properties_.width;
}

auto DesktopWindow::setHeight(int32_t height) noexcept -> void {
  glfwSetWindowSize(window_, properties_.width, height);
}

auto DesktopWindow::getHeight() const noexcept -> int32_t {
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
  props->width = width;
  props->height = height;

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
                                    int /*scancode*/, int action,
                                    int /*mods*/) noexcept -> void {
  if (action == GLFW_PRESS) {
    EventBus::publish<KeyDownEvent>(static_cast<Key>(key));
  } else {
    EventBus::publish<KeyUpEvent>(static_cast<Key>(key));
  }

  // TODO(laurensnol): Properly implement Event with mods
}

auto DesktopWindow::glfwMouseButtonCallback(GLFWwindow * /*window*/, int button,
                                            int action, int /*mods*/) noexcept
    -> void {
  if (action == GLFW_PRESS) {
    EventBus::publish<MouseButtonDownEvent>(static_cast<MouseButton>(button));
  } else {
    EventBus::publish<MouseButtonUpEvent>(static_cast<MouseButton>(button));
  }

  // TODO(laurensnol): Properly implement Event with mods
}

auto DesktopWindow::glfwCursorPosCallback(GLFWwindow * /*window*/, double xpos,
                                          double ypos) noexcept -> void {
  auto event = MouseMoveEvent({xpos, ypos});
  EventBus::publish(event);
}

auto DesktopWindow::glfwScrollCallback(GLFWwindow * /*window*/, double xoffset,
                                       double yoffset) -> void {
  auto event = MouseScrollEvent({xoffset, yoffset});
  EventBus::publish(event);
}
}  // namespace slim
