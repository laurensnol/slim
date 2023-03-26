#ifndef SLIM_CORE_WINDOW_H
#define SLIM_CORE_WINDOW_H

#include <string>
#include <string_view>
#include <memory>
#include <glm/glm.hpp>

namespace slim
{
  struct WindowProperties
  {
    WindowProperties(std::string_view title, uint16_t width, uint16_t height, bool vsync)
      : title(title), width(width), height(height), vsync(vsync) {}

    WindowProperties() = default;

    std::string title;
    uint16_t width;
    uint16_t height;
    bool vsync;
  };

  class Window
  {
  public:
    virtual ~Window() = default;

    virtual bool shouldClose() = 0;
    virtual void update() = 0;
    virtual void *getNative() const = 0;

    virtual WindowProperties getProperties() const = 0;

    virtual glm::vec2 getDimensions() const = 0;
    virtual void setWidth(float width) = 0;
    virtual void setHeight(float height) = 0;

    virtual bool getVsync() const = 0;
    virtual void setVsync(bool value) = 0;

    static std::unique_ptr<Window> create(std::string_view title = "Slim", uint16_t width = 1920, uint16_t height = 1080, bool vsync = false);
  };
}

#endif