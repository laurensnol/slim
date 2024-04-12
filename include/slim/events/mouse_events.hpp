#ifndef SLIM_EVENTS_MOUSE_EVENTS_HPP_
#define SLIM_EVENTS_MOUSE_EVENTS_HPP_

// IWYU pragma: no_include <glm/detail/qualifier.hpp>

#include <cstdint>
#include <glm/ext/vector_float2.hpp>

#include "slim/events/event.hpp"

namespace slim {
// Forward declaration
enum class MouseButton : uint8_t;

/**
 * \brief This event indicates that a mouse button was released.
 *
 * \param button The \ref MouseButton that was released.
 *
 * \ingroup events
 */
class MouseButtonUpEvent : public Event {
public:
  SLIM_DEFINE_EVENT(MouseButtonUp);

  explicit MouseButtonUpEvent(MouseButton button) noexcept : button_(button) {}

  [[nodiscard]] auto getButton() const noexcept -> MouseButton {
    return button_;
  }

private:
  MouseButton button_;
};

/**
 * \brief This event indicates that a mouse button was pressed.
 *
 * \param button The \ref MouseButton that was released.
 *
 * \ingroup events
 */
class MouseButtonDownEvent : public Event {
public:
  SLIM_DEFINE_EVENT(MouseButtonDown);

  explicit MouseButtonDownEvent(MouseButton button) noexcept
      : button_(button) {}

  [[nodiscard]] auto getButton() const noexcept -> MouseButton {
    return button_;
  }

private:
  MouseButton button_;
};

/**
 * \brief This event indicates that the mouse was moved.
 *
 * \param position A \ref glm::vec2 of the position.
 *
 * \ingroup events
 */
class MouseMoveEvent : public Event {
public:
  SLIM_DEFINE_EVENT(MouseMove);

  explicit MouseMoveEvent(const glm::vec2 &position) noexcept
      : position_(position) {}

  [[nodiscard]] auto getPosition() const noexcept -> const glm::vec2 & {
    return position_;
  }

private:
  glm::vec2 position_;
};

/**
 * \brief This event indicates that the scroll wheel's position has changed.
 *
 * \param A \ref glm::vec2 of the mouse wheel's offset.
 *
 * \ingroup events
 */
class MouseScrollEvent : public Event {
public:
  SLIM_DEFINE_EVENT(MouseScroll);

  explicit MouseScrollEvent(const glm::vec2 &offset) noexcept
      : offset_(offset) {}

  [[nodiscard]] auto getOffset() const noexcept -> const glm::vec2 & {
    return offset_;
  }

private:
  glm::vec2 offset_;
};
}  // namespace slim

#endif  // SLIM_EVENTS_MOUSE_EVENTS_HPP_
