#ifndef SLIM_EVENTS_KEY_EVENTS_HPP_
#define SLIM_EVENTS_KEY_EVENTS_HPP_

#include "slim/events/event.hpp"
#include "slim/input/codes.hpp"
namespace slim {
/**
 * \brief This event indicates that a key was released.
 *
 * \param key The \ref Key that was released.
 *
 * \ingroup events
 */
class KeyUpEvent : public Event {
public:
  SLIM_DEFINE_EVENT(KeyUp);

  explicit KeyUpEvent(Key key) noexcept : key_(key) {}

  [[nodiscard]] auto getKey() const noexcept -> Key { return key_; }

private:
  Key key_;
};

/**
 * \brief This event indicates that a key was pressed.
 *
 * \param key The \ref Key that was pressed.
 *
 * \ingroup events
 */
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
