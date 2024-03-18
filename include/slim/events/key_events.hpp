#ifndef SLIM_EVENTS_KEY_EVENTS_HPP_
#define SLIM_EVENTS_KEY_EVENTS_HPP_

#include "slim/events/event.hpp"
#include "slim/input/codes.hpp"
namespace slim {
class KeyUpEvent : public Event {
public:
  SLIM_DEFINE_EVENT(KeyUp);

  explicit KeyUpEvent(Key key) noexcept : key_(key) {}

  [[nodiscard]] auto getKey() const noexcept -> Key { return key_; }

private:
  Key key_;
};

class KeyDownEvent : public Event {
public:
  SLIM_DEFINE_EVENT(KeyDown);

  explicit KeyDownEvent(Key key) noexcept : key_(key) {}

  [[nodiscard]] auto getKey() const noexcept -> Key { return key_; }

private:
  Key key_;
};
}  // namespace slim

#endif  // SLIM_EVENTS_KEY_EVENTS_HPP_
