#ifndef SLIM_INPUT_HPP_
#define SLIM_INPUT_HPP_

#include <glm/ext/vector_float2.hpp>
#include <memory>

#include "slim/input/codes.hpp"  // IWYU pragma: keep
#include "slim/input/input_provider.hpp"

namespace slim {
/**
 * \brief The main input class.
 *
 * This class is a wrapper for common methods concerning inputs.
 *
 * \ingroup input
 */
class Input final {
public:
  /**
   * \brief Initilizes the input subsystem. Will be called by \ref
   *        Application::init.
   *
   * This method will initialize the input subsystem by creating the appropriate
   * \ref InputProvider.
   */
  static auto init() noexcept -> void;

  /**
   * \brief Checks whether the given key is released.
   *
   * \param key The \ref Key to check.
   *
   * \return `true` if released, `false` if not.
   */
  [[nodiscard]] static auto isKeyUp(Key key) noexcept -> bool;

  /**
   * \brief Checks whether the given key is pressed.
   *
   * \param key The \ref Key to check.
   *
   * \return `true` if pressed, `false` if not.
   */
  [[nodiscard]] static auto isKeyDown(Key key) noexcept -> bool;

  /**
   * \brief Checks whether the given mouse button is released.
   *
   * \param button The \ref MouseButton to check.
   *
   * \return `true` if released, `false` if not.
   */
  [[nodiscard]] static auto isMouseButtonUp(MouseButton button) noexcept
      -> bool;

  /**
   * \brief Checks whether the given mouse button is pressed.
   *
   * \param button The \ref MouseButton to check.
   *
   * \return `true` if pressed, `false` if not.
   */
  [[nodiscard]] static auto isMouseButtonDown(MouseButton button) noexcept
      -> bool;

  /**
   * \brief Returns the current mouse position.
   *
   * \return \ref glm::vec2 with x and y coordinates.
   */
  [[nodiscard]] static auto getMousePosition() noexcept -> glm::vec2;

  /**
   * \brief Returns the current mouse scroll offset.
   *
   * \return \ref glm::vec2 with x and y offset.
   */
  [[nodiscard]] static auto getMouseScroll() noexcept -> glm::vec2;

private:
  inline static std::unique_ptr<InputProvider> provider_ = nullptr;
};
}  // namespace slim

#endif  // SLIM_INPUT_HPP_
