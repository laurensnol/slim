#ifndef SLIM_EVENTS_EVENT_HANDLER_HPP_
#define SLIM_EVENTS_EVENT_HANDLER_HPP_

#include <concepts>
#include <cstdint>
#include <functional>

#include "slim/events/event.hpp"
#include "slim/events/event_bus.hpp"

namespace slim {
/**
 * \brief An interface for handling a specific \ref Event on the \ref EventBus.
 *
 * This class defines an interface for classes to listen to an \ref Event on the
 * \ref EventBus by automatically subscribing and unsubscribing from it.
 * The constructor/destructor will call \ref EventBus::subscribe and \ref
 * EventBus::unsubscribe respectively.
 * Implementing this interface requires implementation of the \ref onEvent
 * method for the specified EventType.
 *
 * \tparam The \ref Event to handle. Must be a subclass of \ref Event.
 *
 * \ingroup events
 */
template <typename EventType>
  requires std::derived_from<EventType, Event>
class EventHandler {
public:
  EventHandler(const EventHandler & /*other*/) noexcept
      : handle_(EventBus::subscribe<EventType>(
            std::bind(&EventHandler::onEvent, this, std::placeholders::_1))) {}

  EventHandler(EventHandler &&other) noexcept
      : handle_(EventBus::subscribe<EventType>(
            std::bind(&EventHandler::onEvent, this, std::placeholders::_1))) {
    other.handle_ = EventBus::kInvalidHandle;
  }

  auto operator=(const EventHandler &other) noexcept -> EventHandler & {
    if (this != &other) {
      handle_ = EventBus::subscribe<EventType>(
          std::bind(&EventHandler::onEvent, this, std::placeholders::_1));
    }

    return *this;
  }

  auto operator=(EventHandler &&other) noexcept -> EventHandler & {
    if (this != &other) {
      handle_ = EventBus::subscribe<EventType>(
          std::bind(&EventHandler::onEvent, this, std::placeholders::_1));
      other.handle_ = EventBus::kInvalidHandle;
    }

    return *this;
  }

  virtual ~EventHandler() {
    EventBus::unsubscribe<EventType>(handle_);
    handle_ = EventBus::kInvalidHandle;
  }

  virtual auto onEvent(const EventType &event) noexcept -> void = 0;

protected:
  EventHandler() noexcept
      : handle_(EventBus::subscribe<EventType>(
            std::bind(&EventHandler::onEvent, this, std::placeholders::_1))) {}

  [[nodiscard]] auto getHandle() const noexcept -> uint64_t { return handle_; }

private:
  uint64_t handle_;
};
}  // namespace slim

#endif  // SLIM_EVENTS_EVENT_HANDLER_HPP_
