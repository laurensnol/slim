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
    KeyDownEvent(Key keyCode, uint8_t modifiers)
      : keyCode(keyCode), modifiers(modifiers) { }

    Key keyCode;
    uint8_t modifiers;
  };

  /**
   * KeyUpEvent
   */
  class KeyUpEvent : public Event
  {
  public:
    KeyUpEvent(Key keyCode, uint8_t modifiers)
      : keyCode(keyCode), modifiers(modifiers) { }

    Key keyCode;
    uint8_t modifiers;
  };
}

#endif