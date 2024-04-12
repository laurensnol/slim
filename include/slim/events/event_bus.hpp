#ifndef SLIM_EVENTS_EVENT_BUS_HPP_
#define SLIM_EVENTS_EVENT_BUS_HPP_

#include <algorithm>
#include <concepts>
#include <cstdint>
#include <functional>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <utility>
#include <vector>

namespace slim {
// Forward declaration
class Event;

/**
 * \brief An event bus for immediate handling of an \ref Event.
 *
 * This EventBus is used for immediate handling of an \ref Event.
 * Classes may inherit the \ref EventHandler interface with a specific \ref
 * Event implementation to automatically register it to the EventBus.
 *
 * Any published \ref Event will be immediately handled by all registered
 * handlers.
 *
 * \ingroup events
 */
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
  /**
   * \brief The constant for an invalid handle.
   */
  static const uint64_t kInvalidHandle = 0;

  /**
   * \brief Registers the callback as a handler for an \ref Event.
   *
   * This method registers the passed callback as a handler for the given Event
   * and returns the handle.
   *
   * \tparam EventType The Event to handle. Must be a subclass of \ref Event.
   * \param callback The callback to be called when the event ocurrs.
   *
   * \return The handle of the registered event.
   */
  template <typename EventType>
    requires std::derived_from<EventType, Event>
  static auto subscribe(const CallbackFun<EventType> &callback) noexcept
      -> uint64_t {
    auto ptr = std::unique_ptr<Callback>(
        new CallbackImpl<EventType>{{callbackHandle_}, callback});
    callbacks_[typeid(EventType)].push_back(std::move(ptr));

    return callbackHandle_++;
  }

  /**
   * \brief Unregisteres the callback from the list of handlers.
   *
   * This method will remove the callback with the given handle from the list of
   * handlers.
   *
   * \tparam EventType The Event that the callback was registered for. Must be a
   *         subclass of \ref Event.
   * \param handle The handle of the callback.
   */
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

  /**
   * \brief Instanciates and publishes the \ref Event with the given arguments.
   *
   * This method is a convenience method for constructing *and* publishing an
   * \ref Event by passing the arguments to the Event and publishing it to all
   * handlers.
   *
   * \tparam EventType The type of \ref Event. Must be a subclass of \ref Event.
   * \tparam Args Template parameter pack of arguments.
   * \param args The arguments to be passed to the event.
   */
  template <typename EventType, typename... Args>
    requires std::derived_from<EventType, Event>
  static auto publish(Args... args) noexcept -> void {
    auto event = EventType(args...);
    publish(event);
  }

  /**
   * \brief Publishes an \ref Event.
   *
   * This method publishes the passed \ref Event to all handlers listening to
   * the EventType.
   *
   * \tparam EventType The type of \ref Event. Must be a subclass of \ref Event.
   * \param event The event to be published.
   */
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
