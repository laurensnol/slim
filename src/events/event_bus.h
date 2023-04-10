#ifndef SLIM_EVENTBUS_H
#define SLIM_EVENTBUS_H

#include "events/event.h"
#include <map>
#include <vector>
#include <functional>

namespace slim
{
  class EventBus
  {
  public:
    EventBus(EventBus const&) = delete;
    void operator=(EventBus const&) = delete;

    static void init();
    static EventBus& getInstance();
    static void subscribe(EventType type, const std::function<void(const Event&)>& func);
    static void post(Event& e);

  private:
    EventBus() { };

    static EventBus* s_instance;
    static std::map<EventType, std::vector<std::function<void(const Event&)>>> s_subscribers;
  };
}

#endif