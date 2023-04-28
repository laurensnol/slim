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
    KeyDownEvent(Key key, uint8_t modifiers)
      : key(key), modifiers(modifiers) { }

    Key key;
    uint8_t modifiers;
  };

  /**
   * KeyUpEvent
   */
  class KeyUpEvent : public Event
  {
  public:
    KeyUpEvent(Key key, uint8_t modifiers)
      : key(key), modifiers(modifiers) { }

    Key key;
    uint8_t modifiers;
  };
}

#endif