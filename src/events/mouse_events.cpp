#include "events/mouse_events.h"

namespace slim
{
  /**
   * MouseDownEvent implementation
   */
  MouseDownEvent::MouseDownEvent(MouseButton mouseButton, uint8_t modifiers)
    : mouseButton(mouseButton), modifiers(modifiers) { }

  EventType MouseDownEvent::getType() const
  {
    return EventType::MouseDown;
  }

  /**
   * MouseUpEvent implementation
   */
  MouseUpEvent::MouseUpEvent(MouseButton mouseButton, uint8_t modifiers)
    : mouseButton(mouseButton), modifiers(modifiers) { }

  EventType MouseUpEvent::getType() const
  {
    return EventType::MouseUp;
  }

  /**
   * MouseMoveEvent implementation
   */
  MouseMoveEvent::MouseMoveEvent(glm::vec2 position)
    : position(position) { }

  EventType MouseMoveEvent::getType() const
  {
    return EventType::MouseMove;
  }

  /**
   * MouseScrollEvent implementation
   */
  MouseScrollEvent::MouseScrollEvent(glm::vec2 delta)
    : delta(delta) { }

  EventType MouseScrollEvent::getType() const
  {
    return EventType::MouseScroll;
  }
}