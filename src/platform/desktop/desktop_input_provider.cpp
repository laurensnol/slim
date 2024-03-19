#include "slim/platform/desktop/desktop_input_provider.hpp"

// IWYU pragma: no_include "glm/detail/qualifier.hpp"
// IWYU pragma: no_include "glm/detail/type_vec2.inl"
// IWYU pragma: no_include "slim/core/window.hpp"

#include <GLFW/glfw3.h>

#include <glm/ext/vector_float2.hpp>

#include "slim/core/application.hpp"
#include "slim/events/mouse_events.hpp"
#include "slim/input/codes.hpp"  // IWYU pragma: keep
#include "slim/platform/desktop/desktop_window.hpp"
#include "slim/utils.hpp"

namespace slim {
DesktopInputProvider::DesktopInputProvider() noexcept {
  const auto& window =
      dynamic_cast<const DesktopWindow&>(Application::getWindow());
  window_ = window.window_;
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

auto DesktopInputProvider::onEvent(const MouseScrollEvent& event) noexcept
    -> void {
  scroll_ = event.getOffset();
}
}  // namespace slim
