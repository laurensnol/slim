#ifndef SLIM_EVENTS_EVENT_HPP_
#define SLIM_EVENTS_EVENT_HPP_

#define SLIM_DEFINE_EVENT(name)       \
  static constexpr Type type = #name; \
  [[nodiscard]] auto getType() const noexcept -> Type override { return type; }

namespace slim {
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
