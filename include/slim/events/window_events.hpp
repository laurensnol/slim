#ifndef SLIM_EVENTS_WINDOW_EVENTS_HPP_
#define SLIM_EVENTS_WINDOW_EVENTS_HPP_

#include <cstdint>

#include "slim/events/event.hpp"

namespace slim {
class WindowCloseEvent : public Event {
public:
  SLIM_DEFINE_EVENT(WindowClose);

  WindowCloseEvent() noexcept = default;
};

class WindowResizeEvent : public Event {
public:
  SLIM_DEFINE_EVENT(WindowResize);

  WindowResizeEvent(uint64_t width, uint64_t height) noexcept
      : width_(width), height_(height) {}

  [[nodiscard]] auto getWidth() const noexcept -> uint64_t { return width_; }
  [[nodiscard]] auto getHeight() const noexcept -> uint64_t { return height_; }

private:
  uint64_t width_;
  uint64_t height_;
};

class WindowFocusEvent : public Event {
public:
  SLIM_DEFINE_EVENT(WindowFocus);

  explicit WindowFocusEvent(bool focused) noexcept : focused_(focused) {}

  [[nodiscard]] auto getFocused() const noexcept -> bool { return focused_; }

private:
  bool focused_;
};

class WindowMinimizeEvent : public Event {
public:
  SLIM_DEFINE_EVENT(WindowMinimize);

  explicit WindowMinimizeEvent(bool minimized) noexcept
      : minimized_(minimized) {}

  [[nodiscard]] auto getMinimized() const noexcept -> bool {
    return minimized_;
  }

private:
  bool minimized_;
};
}  // namespace slim

#endif  // SLIM_EVENTS_WINDOW_EVENTS_HPP_
