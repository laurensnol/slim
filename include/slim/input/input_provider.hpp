#ifndef SLIM_INPUT_INPUT_PROVIDER_HPP_
#define SLIM_INPUT_INPUT_PROVIDER_HPP_

#include <glm/ext/vector_float2.hpp>

#include "slim/input/codes.hpp"

namespace slim {
/**
 * \brief The abstract base input provider interface.
 *
 * This interface defines a base for implementing input methods for various
 * platforms which will be wrapped by \ref Input.
 *
 * \ingroup input
 */
class InputProvider {  // NOLINT(cppcoreguidelines-special-member-functions)
public:
  virtual ~InputProvider() = default;

  /**
   * \name Interface methods.
   *
   * Virtual methods that require implementation.
   */
  ///@{
  [[nodiscard]] virtual auto isKeyUp(Key key) const noexcept -> bool = 0;
  [[nodiscard]] virtual auto isKeyDown(Key key) const noexcept -> bool = 0;

  [[nodiscard]] virtual auto isMouseButtonUp(MouseButton button) const noexcept
      -> bool = 0;
  [[nodiscard]] virtual auto isMouseButtonDown(
      MouseButton button) const noexcept -> bool = 0;

  [[nodiscard]] virtual auto getMousePosition() const noexcept -> glm::vec2 = 0;
  [[nodiscard]] virtual auto getMouseScroll() const noexcept -> glm::vec2 = 0;
  ///@}
};
}  // namespace slim

#endif  // SLIM_INPUT_INPUT_PROVIDER_HPP_
