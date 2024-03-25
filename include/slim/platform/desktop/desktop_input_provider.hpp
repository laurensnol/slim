#ifndef SLIM_PLATFORM_DESKTOP_INPUT_PROVIDER_HPP_
#define SLIM_PLATFORM_DESKTOP_INPUT_PROVIDER_HPP_

#include <GLFW/glfw3.h>

#include <glm/detail/qualifier.hpp>
#include <glm/ext/vector_float2.hpp>

#include "slim/input/codes.hpp"  // IWYU pragma: keep
#include "slim/input/input_provider.hpp"

namespace slim {
class DesktopInputProvider : public InputProvider {
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

private:
  GLFWwindow *window_;
  glm::vec2 scroll_ = {};

  // GLFW callbacks

  static auto glfwKeyCallback(GLFWwindow *window, int key, int scancode,
                              int action, int mods) noexcept -> void;
  static auto glfwMouseButtonCallback(GLFWwindow *window, int button,
                                      int action, int mods) noexcept -> void;
  static auto glfwCursorPosCallback(GLFWwindow *window, double xpos,
                                    double ypos) noexcept -> void;
  static auto glfwScrollCallback(GLFWwindow *window, double xoffset,
                                 double yoffset) -> void;
};
}  // namespace slim

#endif  // SLIM_PLATFORM_DESKTOP_INPUT_PROVIDER_HPP_
