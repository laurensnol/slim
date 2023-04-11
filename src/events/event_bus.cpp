#include "events/event_bus.h"

namespace slim
{
  EventBus* EventBus::s_instance = nullptr;
  std::unordered_map<std::type_index, std::vector<std::unique_ptr<EventBus::_Callback>>> EventBus::s_subscribers = {};
  int32_t EventBus::s_callbackIdCounter = 0;

  void EventBus::init()
  {
    if (!s_instance)
      s_instance = new EventBus();
  }
}