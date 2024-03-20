#ifndef SLIM_EVENTS_WINDOW_EVENTS_HPP_
#define SLIM_EVENTS_WINDOW_EVENTS_HPP_

#include <glm/ext/vector_int2.hpp>

#include "slim/events/event.hpp"

namespace slim {
/**
 * \brief This event indicates that the window was closed.
 *
 * \ingroup events
 */
class WindowCloseEvent : public Event {
public:
  SLIM_DEFINE_EVENT(WindowClose);

  WindowCloseEvent() noexcept = default;
};

/**
 * \brief This event indicates a change of the framebuffer's size.
 *
 * \param dimensions glm::ivec2 of the width and height in pixels.
 *
 * \ingroup events
 */
class WindowResizeEvent : public Event {
public:
  SLIM_DEFINE_EVENT(WindowResize);

  explicit WindowResizeEvent(const glm::ivec2 &dimensions) noexcept
      : dimensions_(dimensions) {}

  [[nodiscard]] auto getDimensions() const noexcept -> const glm::ivec2 & {
    return dimensions_;
  }

private:
  glm::ivec2 dimensions_;
};

/**
 * \brief This event indicates a change of the window's focus.
 *
 * \param focused Whether the window is focused (`true`) or not (`false`).
 *
 * \ingroup events
 */
class WindowFocusEvent : public Event {
public:
  SLIM_DEFINE_EVENT(WindowFocus);

  explicit WindowFocusEvent(bool focused) noexcept : focused_(focused) {}

  [[nodiscard]] auto getFocused() const noexcept -> bool { return focused_; }

private:
  bool focused_;
};

/**
 * \brief This event indicates that the window was minimized or maximized.
 *
 * \param Whether the window was minimized (`true`) or maximized (`false`).
 *
 * \ingroup events
 */
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
