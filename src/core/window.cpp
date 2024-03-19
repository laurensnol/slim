#include "slim/core/window.hpp"

#include <cstdint>
#include <memory>
#include <string>

#include "slim/platform/desktop/desktop_window.hpp"

namespace slim {
auto Window::create(const std::string &title, uint16_t width, uint16_t height,
                    bool vsync, bool focused, bool minimized) noexcept
    -> std::unique_ptr<Window> {
#ifdef SLIM_PLATFORM_WINDOWS
  return std::make_unique<DesktopWindow>(title, width, height, vsync, focused,
                                         minimized);
#elif SLIM_PLATFORM_LINUX
  return std::make_unique<DesktopWindow>(title, width, height, vsync, focused,
                                         minimized);
#elif SLIM_PLATFORM_MACOS
  return std::make_unique<DesktopWindow>(title, width, height, vsync, focused,
                                         minimized);
#else
  // NOLINTNEXTLINE
  static_assert(false, "SLIM_PLATFORM not defined");
#endif
}
}  // namespace slim
