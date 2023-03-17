#include "core/window.h"

#ifdef SLIM_PLATFORM_MACOS
  #include "platform/MacOS/MacOSWindow.h"
#endif

namespace slim
{
  std::unique_ptr<Window> Window::create(std::string_view title, uint16_t width, uint16_t height)
  {
    WindowProperties properties = {title, width, height};

    #ifdef SLIM_PLATFORM_MACOS
      return std::make_unique<MacOSWindow>(properties);
    #else
      spdlog::critical("Platform not implemented");
      assert(false);
    #endif
  }
}