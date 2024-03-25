#include "slim/platform/desktop/desktop_input_provider.hpp"

// IWYU pragma: no_include "glm/detail/qualifier.hpp"
// IWYU pragma: no_include "glm/detail/type_vec2.inl"
// IWYU pragma: no_include "slim/core/window.hpp"

#include <GLFW/glfw3.h>

#include <glm/ext/vector_float2.hpp>

#include "slim/core/application.hpp"
#include "slim/events/event_bus.hpp"
#include "slim/events/key_events.hpp"
#include "slim/events/mouse_events.hpp"
#include "slim/input/codes.hpp"  // IWYU pragma: keep
#include "slim/platform/desktop/desktop_window.hpp"
#include "slim/ui/ui.hpp"
#include "slim/utils.hpp"

namespace slim {
DesktopInputProvider::DesktopInputProvider() noexcept {
  const auto& window =
      dynamic_cast<const DesktopWindow&>(Application::getWindow());
  window_ = window.window_;

  glfwSetKeyCallback(window_, glfwKeyCallback);
  glfwSetMouseButtonCallback(window_, glfwMouseButtonCallback);
  glfwSetCursorPosCallback(window_, glfwCursorPosCallback);
  glfwSetScrollCallback(window_, glfwScrollCallback);
}

auto DesktopInputProvider::isKeyUp(Key key) const noexcept -> bool {
  return glfwGetKey(window_, +key) == GLFW_RELEASE;
}

auto DesktopInputProvider::isKeyDown(Key key) const noexcept -> bool {
  return glfwGetKey(window_, +key) == GLFW_PRESS;
}

auto DesktopInputProvider::isMouseButtonUp(MouseButton button) const noexcept
    -> bool {
  return glfwGetMouseButton(window_, +button) == GLFW_RELEASE;
}

auto DesktopInputProvider::isMouseButtonDown(MouseButton button) const noexcept
    -> bool {
  return glfwGetMouseButton(window_, +button) == GLFW_PRESS;
}

auto DesktopInputProvider::getMousePosition() const noexcept -> glm::vec2 {
  double xPos = 0;
  double yPos = 0;
  glfwGetCursorPos(window_, &xPos, &yPos);

  return {xPos, yPos};
}

auto DesktopInputProvider::getMouseScroll() const noexcept -> glm::vec2 {
  return scroll_;
}

auto DesktopInputProvider::glfwKeyCallback(GLFWwindow* /*window*/, int key,
                                           int /*scancode*/, int action,
                                           int /*mods*/) noexcept -> void {
  if (!UI::capturesKeyboard()) {
    if (action == GLFW_PRESS) {
      EventBus::publish<KeyDownEvent>(static_cast<Key>(key));
    } else {
      EventBus::publish<KeyUpEvent>(static_cast<Key>(key));
    }
  }

  // TODO(laurensnol): Properly implement Event with mods
}

auto DesktopInputProvider::glfwMouseButtonCallback(GLFWwindow* /*window*/,
                                                   int button, int action,
                                                   int /*mods*/) noexcept
    -> void {
  if (!UI::capturesMouse()) {
    if (action == GLFW_PRESS) {
      EventBus::publish<MouseButtonDownEvent>(static_cast<MouseButton>(button));
    } else {
      EventBus::publish<MouseButtonUpEvent>(static_cast<MouseButton>(button));
    }
  }

  // TODO(laurensnol): Properly implement Event with mods
}

auto DesktopInputProvider::glfwCursorPosCallback(GLFWwindow* /*window*/,
                                                 double xpos,
                                                 double ypos) noexcept -> void {
  if (!UI::capturesMouse()) {
    auto event = MouseMoveEvent({xpos, ypos});
    EventBus::publish(event);
  }
}

auto DesktopInputProvider::glfwScrollCallback(GLFWwindow* /*window*/,
                                              double xoffset, double yoffset)
    -> void {
  if (!UI::capturesMouse()) {
    auto event = MouseScrollEvent({xoffset, yoffset});
    EventBus::publish(event);
  }
}
}  // namespace slim
