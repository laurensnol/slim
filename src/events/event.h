#ifndef SLIM_EVENT_H
#define SLIM_EVENT_H

namespace slim
{
  enum EventType
  {
    WindowClose,
    WindowResize,
    WindowFocus,
    WindowMinimize,

    KeyDown,
    KeyUp,

    MouseDown,
    MouseUp,
    MouseMove,
    MouseScroll
  };

  class Event
  {
  public:
    virtual ~Event() = default;

    virtual EventType getType() const = 0;
  };
}

#endif