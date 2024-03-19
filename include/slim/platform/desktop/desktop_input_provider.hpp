#ifndef SLIM_PLATFORM_DESKTOP_INPUT_PROVIDER_HPP_
#define SLIM_PLATFORM_DESKTOP_INPUT_PROVIDER_HPP_

#include <GLFW/glfw3.h>

#include <glm/detail/qualifier.hpp>
#include <glm/ext/vector_float2.hpp>

#include "slim/events/event_handler.hpp"
#include "slim/events/mouse_events.hpp"
#include "slim/input/codes.hpp"  // IWYU pragma: keep
#include "slim/input/input_provider.hpp"

namespace slim {
class DesktopInputProvider : public InputProvider,
                             EventHandler<MouseScrollEvent> {
public:
  DesktopInputProvider() noexcept;

  [[nodiscard]] auto isKeyUp(Key key) const noexcept -> bool override;
  [[nodiscard]] auto isKeyDown(Key key) const noexcept -> bool override;

  [[nodiscard]] auto isMouseButtonUp(MouseButton button) const noexcept
      -> bool override;
  [[nodiscard]] auto isMouseButtonDown(MouseButton button) const noexcept
      -> bool override;

  [[nodiscard]] auto getMousePosition() const noexcept -> glm::vec2 override;
  [[nodiscard]] auto getMouseScroll() const noexcept -> glm::vec2 override;

  auto onEvent(const MouseScrollEvent& event) noexcept -> void override;

private:
  GLFWwindow* window_;
  glm::vec2 scroll_ = {};
};
}  // namespace slim

#endif  // SLIM_PLATFORM_DESKTOP_INPUT_PROVIDER_HPP_
