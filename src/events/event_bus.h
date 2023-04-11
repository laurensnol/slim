#ifndef SLIM_EVENTBUS_H
#define SLIM_EVENTBUS_H

#include "events/event.h"
#include <cstdint>
#include <functional>
#include <typeinfo>
#include <memory>
#include <algorithm>
#include <unordered_map>
#include <typeindex>
#include <vector>

namespace slim
{
  class EventBus
  {
  public:
    EventBus(EventBus const&) = delete;
    void operator=(EventBus const&) = delete;

    static void init();

    template <typename T>
    static int32_t subscribe(const std::function<void(const T&)>& func)
    {
      static_assert(std::is_base_of<Event, T>());

      std::unique_ptr<_Callback> callback = std::unique_ptr<_Callback>(new _EventCallback<T>(s_callbackIdCounter, func));
      s_subscribers[typeid(T)].push_back(std::move(callback));

      return s_callbackIdCounter++;
    }

    template <typename T>
    static void unsubscribe(int32_t id)
    {
      auto& vec = s_subscribers[typeid(T)];
      vec.erase(std::remove_if(vec.begin(), vec.end(), [id](const std::unique_ptr<_Callback>& callback)
      {
        return callback->id == id;
      }));
    }

    // Note: Providing T is not necessary.
    template <typename T>
    static void publish(const T& event)
    {
      static_assert(std::is_base_of<Event, T>());

      std::type_index type = typeid(T);

      if (s_subscribers.find(type) == s_subscribers.end())
        return;

      for (auto&& function : s_subscribers[type])
      {
        _EventCallback<T>* eventCallback = static_cast<_EventCallback<T>*>(function.get());
        auto callback = static_cast<std::function<void(const T&)>>(eventCallback->func);
        callback(event);
      }
    }

  private:
    struct _Callback
    {
      _Callback(int32_t id) : id(id) { }
      virtual ~_Callback() = default;

      int32_t id;
    };

    template <typename T>
    struct _EventCallback : public _Callback
    {
      _EventCallback(int32_t id, std::function<void(const T&)> func)
        : _Callback(id), func(func) { }
      
      std::function<void(const T&)> func;
    };

    EventBus() { };

    static EventBus* s_instance;
    static std::unordered_map<std::type_index, std::vector<std::unique_ptr<_Callback>>> s_subscribers;
    static int32_t s_callbackIdCounter;
  };
}

#endif