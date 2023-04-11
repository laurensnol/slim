#ifndef SLIM_MOUSEEVENTS_H
#define SLIM_MOUSEEVENTS_H

#include "events/event.h"
#include "events/codes.h"
#include <cstdint>
#include <glm/glm.hpp>

namespace slim
{
  /**
   * MouseDownEvent
   */
  class MouseDownEvent : public Event
  {
  public:
    MouseDownEvent(MouseButton mouseButton, uint8_t modifiers)
      : mouseButton(mouseButton), modifiers(modifiers) { }

    MouseButton mouseButton;
    uint8_t modifiers;
  };

  /**
   * MouseUpEvent
   */
  class MouseUpEvent : public Event
  {
  public:
    MouseUpEvent(MouseButton mouseButton, uint8_t modifiers)
      : mouseButton(mouseButton), modifiers(modifiers) { }
    
    MouseButton mouseButton;
    uint8_t modifiers;
  };

  /**
   * MouseMoveEvent
   */
  class MouseMoveEvent : public Event
  {
  public:
    MouseMoveEvent(glm::vec2 position)
      : position(position) { }

    glm::vec2 position;
  };

  /**
   * MouseScrollEvent
   */
  class MouseScrollEvent : public Event
  {
  public:
    MouseScrollEvent(glm::vec2 delta)
      : delta(delta) { }

    glm::vec2 delta;
  };
}

#endif