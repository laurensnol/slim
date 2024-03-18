#ifndef SLIM_EVENTS_MOUSE_EVENTS_HPP_
#define SLIM_EVENTS_MOUSE_EVENTS_HPP_

#include <glm/ext/vector_float2.hpp>

#include "slim/events/event.hpp"
#include "slim/input/codes.hpp"

namespace slim {
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
