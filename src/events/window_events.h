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
    WindowCloseEvent(Window* window);
    
    EventType getType() const override;

    Window* window;
  };

  /**
   * WindowResizeEvent
   */
  class WindowResizeEvent : public Event
  {
  public:
    WindowResizeEvent(Window* window, glm::vec2 size);
    
    EventType getType() const override;

    Window* window;
    glm::vec2 size;
  };

  /**
   * WindowFocusEvent
   */
  class WindowFocusEvent : public Event
  {
  public:
    WindowFocusEvent(Window* window, bool focused);

    EventType getType() const override;

    Window* window;
    bool focused;
  };

  /**
   * WindowMinimizeEvent
   */
  class WindowMinimizeEvent : public Event
  {
  public:
    WindowMinimizeEvent(Window* window, bool minimized);

    EventType getType() const override;

    Window* window;
    bool minimized;
  };
}

#endif