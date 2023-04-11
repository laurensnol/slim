#ifndef SLIM_WINDOWEVENT_H
#define SLIM_WINDOWEVENT_H

#include "events/event.h"
#include "core/window.h"
#include <glm/glm.hpp>

namespace slim
{
  /**
   * WindowCloseEvent
   */
  class WindowCloseEvent : public Event
  {
  public:
    WindowCloseEvent(Window* window)
      : window(window) { }

    Window* window;
  };

  /**
   * WindowResizeEvent
   */
  class WindowResizeEvent : public Event
  {
  public:
    WindowResizeEvent(Window* window, glm::vec2 size)
      : window(window), size(size) { }

    Window* window;
    glm::vec2 size;
  };

  /**
   * WindowFocusEvent
   */
  class WindowFocusEvent : public Event
  {
  public:
    WindowFocusEvent(Window* window, bool focused)
      : window(window), focused(focused) { }

    Window* window;
    bool focused;
  };

  /**
   * WindowMinimizeEvent
   */
  class WindowMinimizeEvent : public Event
  {
  public:
    WindowMinimizeEvent(Window* window, bool minimized)
      : window(window), minimized(minimized) { }

    Window* window;
    bool minimized;
  };
}

#endif