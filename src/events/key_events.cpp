#include "events/key_events.h"

namespace slim
{
  /**
   * KeyDownEvent implementation
   */
  KeyDownEvent::KeyDownEvent(KeyCode keyCode, uint8_t modifiers)
    : keyCode(keyCode), modifiers(modifiers) { }

  EventType KeyDownEvent::getType() const
  {
    return EventType::KeyDown;
  }

  /**
   * KeyUpEvent implementation
   */
  KeyUpEvent::KeyUpEvent(KeyCode keyCode, uint8_t modifiers)
    : keyCode(keyCode), modifiers(modifiers) { }

  EventType KeyUpEvent::getType() const
  {
    return EventType::KeyUp;
  }
}