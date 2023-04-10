#include "events/window_events.h"

namespace slim
{
  /**
   * WindowCloseEvent implementation
   */
  WindowCloseEvent::WindowCloseEvent(Window* window)
    : window(window) { }

  EventType WindowCloseEvent::getType() const
  {
    return EventType::WindowClose;
  }

  /**
   * WindowResizeEvent implementation
   */
  WindowResizeEvent::WindowResizeEvent(Window* window, glm::vec2 size)
    : window(window), size(size) { }

  EventType WindowResizeEvent::getType() const
  {
    return EventType::WindowResize;
  }

  /**
   * WindowFocusEvent implementation
   */
  WindowFocusEvent::WindowFocusEvent(Window* window, bool focused)
    : window(window), focused(focused) { }

  EventType WindowFocusEvent::getType() const
  {
    return EventType::WindowFocus;
  }

  /**
   * WindowMinimizeEvent implementation
   */
  WindowMinimizeEvent::WindowMinimizeEvent(Window* window, bool minimized)
    : window(window), minimized(minimized) { }

  EventType WindowMinimizeEvent::getType() const
  {
    return EventType::WindowMinimize;
  }
}