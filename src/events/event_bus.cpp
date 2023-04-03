#include "events/event_bus.h"
#include "core/base.h"
#include <spdlog/spdlog.h>

namespace slim
{
  EventBus* EventBus::s_instance = nullptr;
  std::map<EventType, std::vector<std::function<void(const Event&)>>> EventBus::s_subscribers = {};

  void EventBus::init()
  {
    if (!s_instance)
      s_instance = new EventBus();
  }

  EventBus& EventBus::getInstance()
  {
    SLIM_ASSERT(s_instance, "EventBus not initialized")
    return *s_instance;
  }

  void EventBus::subscribe(EventType type, const std::function<void(const Event&)>& func)
  {
    s_subscribers[type].push_back(func);
  }

  void slim::EventBus::post(Event& e)
  {
    EventType type = e.getType();
    spdlog::info("Posting event of type {}", (int)type);

    if (s_subscribers.find(type) == s_subscribers.end())
      return;

    for (auto&& func : s_subscribers.at(type))
      func(e);
  }
}