#ifndef SLIM_INPUT_HPP_
#define SLIM_INPUT_HPP_

#include <glm/ext/vector_float2.hpp>
#include <memory>

#include "slim/input/codes.hpp"  // IWYU pragma: keep
#include "slim/input/input_provider.hpp"

namespace slim {
class Input final {
public:
  static auto init() noexcept -> void;

  [[nodiscard]] static auto isKeyUp(Key key) noexcept -> bool;
  [[nodiscard]] static auto isKeyDown(Key key) noexcept -> bool;

  [[nodiscard]] static auto isMouseButtonUp(MouseButton button) noexcept
      -> bool;
  [[nodiscard]] static auto isMouseButtonDown(MouseButton button) noexcept
      -> bool;

  [[nodiscard]] static auto getMousePosition() noexcept -> glm::vec2;
  [[nodiscard]] static auto getMouseScroll() noexcept -> glm::vec2;

private:
  inline static std::unique_ptr<InputProvider> provider_ = nullptr;
};
}  // namespace slim

#endif  // SLIM_INPUT_HPP_
