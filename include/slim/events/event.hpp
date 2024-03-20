#ifndef SLIM_EVENTS_EVENT_HPP_
#define SLIM_EVENTS_EVENT_HPP_

/**
 * \brief A helper macro to define an Event's type and getType() method.
 *
 * \see \ref KeyDownEvent for usage.
 *
 * \ingroup events
 */
#define SLIM_DEFINE_EVENT(name)       \
  static constexpr Type type = #name; \
  [[nodiscard]] auto getType() const noexcept -> Type override { return type; }

namespace slim {
/**
 * \brief The abstract Event interface.
 *
 * This abstract class defines an interface for any Event that may be processed
 * by slim.
 *
 * \see \ref KeyDownEvent for a possible implementation.
 *
 * \ingroup events
 */
class Event {  // NOLINT(cppcoreguidelines-special-member-functions)
protected:
  using Type = const char *;

  Event() = default;

public:
  virtual ~Event() = default;

  [[nodiscard]] virtual auto getType() const noexcept -> Type = 0;
};
}  // namespace slim

#endif  // SLIM_EVENTS_EVENT_HPP_
