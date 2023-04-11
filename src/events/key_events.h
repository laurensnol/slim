#ifndef SLIM_KEYEVENTS_H
#define SLIM_KEYEVENTS_H

#include "events/event.h"
#include "events/codes.h"
#include <cstdint>

namespace slim
{
  /**
   * KeyDownEvent
   */
  class KeyDownEvent : public Event
  {
  public:
    KeyDownEvent(KeyCode keyCode, uint8_t modifiers)
      : keyCode(keyCode), modifiers(modifiers) { }

    KeyCode keyCode;
    uint8_t modifiers;
  };

  /**
   * KeyUpEvent
   */
  class KeyUpEvent : public Event
  {
  public:
    KeyUpEvent(KeyCode keyCode, uint8_t modifiers)
      : keyCode(keyCode), modifiers(modifiers) { }

    KeyCode keyCode;
    uint8_t modifiers;
  };
}

#endif