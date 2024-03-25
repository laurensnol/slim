#include "slim/platform/desktop/desktop_window.hpp"

// IWYU pragma: no_include "glm/detail/qualifier.hpp"
// IWYU pragma: no_include "glm/detail/type_vec2.inl"
// IWYU pragma: no_include "glm/detail/type_vec2.hpp"
// IWYU pragma: no_include "spdlog/common.h"
// IWYU pragma: no_include <spdlog/fmt/fmt.h>

#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <spdlog/spdlog.h>

#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <glm/ext/vector_int2.hpp>
#include <string>
#include <utility>

#include "slim/events/event_bus.hpp"
#include "slim/events/window_events.hpp"
#include "slim/input/codes.hpp"  // IWYU pragma: keep
#include "slim/ui/ui.hpp"

namespace slim {
DesktopWindow::DesktopWindow(std::string title, int32_t width, int32_t height,
                             bool vsync, bool focused, bool minimized) noexcept
    // clang-format off: behaves weirdly here
    : properties_{std::move(title), {width, height}, {width, height}, vsync,
                                     focused, minimized} {
  // clang-format on
  assert(!(focused && minimized));  // A window may not be focused and minimized

  glfwSetErrorCallback(glfwErrorCallback);

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

  window_ = glfwCreateWindow(properties_.windowDimensions.x,
                             properties_.windowDimensions.y,
                             properties_.title.c_str(), nullptr, nullptr);

  assert(window_);

  // Update framebuffer sizes since they might not match window sizes (e.g.
  // retina)
  glfwGetFramebufferSize(window_, &properties_.framebufferDimensions.x,
                         &properties_.framebufferDimensions.y);

  glfwSetWindowUserPointer(window_, &properties_);
  glfwSetWindowCloseCallback(window_, glfwCloseCallback);
  glfwSetWindowSizeCallback(window_, glfwWindowSizeCallback);
  glfwSetFramebufferSizeCallback(window_, glfwFramebufferSizeCallback);
  glfwSetWindowFocusCallback(window_, glfwWindowFocusCallback);
  glfwSetWindowIconifyCallback(window_, glfwWindowIconifyCallback);

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

auto DesktopWindow::setWindowDimensions(const glm::ivec2 &dimensions) noexcept
    -> void {
  glfwSetWindowSize(window_, dimensions.x, dimensions.y);
}

auto DesktopWindow::getWindowDimensions() const noexcept -> const glm::ivec2 & {
  return properties_.windowDimensions;
}

auto DesktopWindow::getFramebufferDimensions() const noexcept
    -> const glm::ivec2 & {
  return properties_.framebufferDimensions;
}

auto DesktopWindow::setWidth(int32_t width) noexcept -> void {
  glfwSetWindowSize(window_, width, properties_.windowDimensions.y);
}

auto DesktopWindow::getWidth() const noexcept -> int32_t {
  return properties_.windowDimensions.x;
}

auto DesktopWindow::setHeight(int32_t height) noexcept -> void {
  glfwSetWindowSize(window_, properties_.windowDimensions.x, height);
}

auto DesktopWindow::getHeight() const noexcept -> int32_t {
  return properties_.windowDimensions.y;
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

auto DesktopWindow::glfwErrorCallback(int code,
                                      const char *description) noexcept
    -> void {
  spdlog::error("GLFW Error: {}, {}", code, description);
  std::abort();
}

auto DesktopWindow::glfwCloseCallback(GLFWwindow * /*window*/) noexcept
    -> void {
  EventBus::publish<WindowCloseEvent>();
}

auto DesktopWindow::glfwWindowSizeCallback(GLFWwindow *window, int width,
                                           int height) noexcept -> void {
  auto *props =
      static_cast<WindowProperties *>(glfwGetWindowUserPointer(window));
  props->windowDimensions = {width, height};

  auto event =
      WindowResizeEvent(props->windowDimensions, props->framebufferDimensions);
  EventBus::publish<WindowResizeEvent>(event);
}

auto DesktopWindow::glfwFramebufferSizeCallback(GLFWwindow *window, int width,
                                                int height) noexcept -> void {
  auto *props =
      static_cast<WindowProperties *>(glfwGetWindowUserPointer(window));
  props->framebufferDimensions = {width, height};

  auto event =
      WindowResizeEvent(props->windowDimensions, props->framebufferDimensions);
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
}  // namespace slim
