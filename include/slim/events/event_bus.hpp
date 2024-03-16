#ifndef SLIM_EVENTS_EVENT_BUS_HPP_
#define SLIM_EVENTS_EVENT_BUS_HPP_

#include <algorithm>
#include <concepts>
#include <cstdint>
#include <functional>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include "slim/events/event.hpp"

namespace slim {
class EventBus {
private:
  struct Callback {
    uint64_t handle;
  };

  using CallbackPtr = std::unique_ptr<Callback>;
  using CallbackPtrVec = std::vector<CallbackPtr>;

  template <typename EventType>
    requires std::derived_from<EventType, Event>
  using CallbackFun = std::function<void(const EventType &)>;

  template <typename EventType>
    requires std::derived_from<EventType, Event>
  struct CallbackImpl : public Callback {
    CallbackFun<EventType> callback;
  };

public:
  static const uint64_t kInvalidHandle = 0;

  template <typename EventType>
    requires std::derived_from<EventType, Event>
  static auto subscribe(const CallbackFun<EventType> &callback) noexcept
      -> uint64_t {
    auto ptr = std::unique_ptr<Callback>(
        new CallbackImpl{{callbackHandle_}, callback});
    callbacks_[typeid(EventType)].push_back(std::move(ptr));

    return callbackHandle_++;
  }

  template <typename EventType>
    requires std::derived_from<EventType, Event>
  static auto unsubscribe(uint64_t handle) noexcept {
    if (handle == kInvalidHandle) {
      return;
    }

    auto iter = callbacks_.find(typeid(EventType));
    if (iter != callbacks_.end()) {
      iter->second.erase(std::remove_if(iter->second.begin(),
                                        iter->second.end(),
                                        [handle](const CallbackPtr &callback) {
                                          return callback->handle == handle;
                                        }));
    }
  }

  template <typename EventType, typename... Args>
    requires std::derived_from<EventType, Event>
  static auto publish(Args... args) noexcept -> void {
    auto event = EventType(args...);
    publish(event);
  }

  template <typename EventType>
    requires std::derived_from<EventType, Event>
  static auto publish(const EventType &event) noexcept -> void {
    for (const auto &callback : callbacks_[typeid(EventType)]) {
      auto impl = static_cast<CallbackImpl<EventType> *>(callback.get());
      impl->callback(event);
    }
  }

private:
  inline static uint64_t callbackHandle_ = 1;
  inline static std::unordered_map<std::type_index, CallbackPtrVec> callbacks_ =
      {};
};
}  // namespace slim

#endif  // SLIM_EVENTS_EVENT_BUS_HPP_
