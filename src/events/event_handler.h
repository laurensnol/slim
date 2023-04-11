#ifndef SLIM_EVENTHANDLER_H
#define SLIM_EVENTHANDLER_H

#include "events/event.h"
#include "events/event_bus.h"
#include <type_traits>
#include <functional>

namespace slim
{
  template <typename T>
  class EventHandler
  {
  public:
    EventHandler()
    {
      static_assert(std::is_base_of<Event, T>());
      m_eventHandlerId = EventBus::subscribe<T>(std::bind(&EventHandler::onEvent, this, std::placeholders::_1));
    }

    virtual ~EventHandler()
    {
      EventBus::unsubscribe<T>(m_eventHandlerId);
    }

    virtual void onEvent(const T& event) = 0;

  protected:
    int32_t m_eventHandlerId;
  };
}

#endif