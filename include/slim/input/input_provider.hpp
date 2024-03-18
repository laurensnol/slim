#ifndef SLIM_INPUT_INPUT_PROVIDER_HPP_
#define SLIM_INPUT_INPUT_PROVIDER_HPP_

#include <glm/ext/vector_float2.hpp>

#include "slim/input/codes.hpp"

namespace slim {
class InputProvider {  // NOLINT(cppcoreguidelines-special-member-functions)
public:
  virtual ~InputProvider() = default;

  [[nodiscard]] virtual auto isKeyUp(Key key) const noexcept -> bool = 0;
  [[nodiscard]] virtual auto isKeyDown(Key key) const noexcept -> bool = 0;

  [[nodiscard]] virtual auto isMouseButtonUp(MouseButton button) const noexcept
      -> bool = 0;
  [[nodiscard]] virtual auto isMouseButtonDown(
      MouseButton button) const noexcept -> bool = 0;

  [[nodiscard]] virtual auto getMousePosition() const noexcept -> glm::vec2 = 0;
  [[nodiscard]] virtual auto getMouseScroll() const noexcept -> glm::vec2 = 0;
};
}  // namespace slim

#endif  // SLIM_INPUT_INPUT_PROVIDER_HPP_
