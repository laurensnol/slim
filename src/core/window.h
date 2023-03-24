#ifndef SLIM_CORE_WINDOW_H
#define SLIM_CORE_WINDOW_H

#include <string>
#include <string_view>
#include <memory>
#include <assert.h>

namespace slim
{
  struct WindowProperties
  {
    WindowProperties(std::string_view title = "Slim", uint16_t width = 1600, uint16_t height = 800)
      : title(title), width(width), height(height) {}

    std::string title;
    uint16_t width;
    uint16_t height;
  };

  class Window
  {
  public:
    virtual ~Window() = default;

    virtual bool shouldClose() = 0;
    virtual void update() = 0;
    virtual void *getNative() = 0;
    virtual WindowProperties getProperties() = 0;

    static std::unique_ptr<Window> create(std::string_view title = "Slim", uint16_t width = 1600, uint16_t height = 900);
  };
}

#endif