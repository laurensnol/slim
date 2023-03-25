#include "core/window.h"

#include "core/base.h"

#ifdef SLIM_PLATFORM_MACOS
  #include "platform/MacOS/MacOSWindow.h"
#endif

namespace slim
{
  std::unique_ptr<Window> Window::create(std::string_view title, uint16_t width, uint16_t height)
  {
    #ifdef SLIM_PLATFORM_MACOS
      return std::make_unique<MacOSWindow>(title, width, height);
    #else
      SLIM_ASSERT(false, "Platform not implemented")
    #endif
  }
}