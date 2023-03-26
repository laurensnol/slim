#ifndef SLIM_MACOSWINDOW
#define SLIM_MACOSWINDOW

#include "core/window.h"
#include <string_view>
#include <glm/glm.hpp>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace slim
{
  class MacOSWindow : public Window
  {
  public:
    MacOSWindow(std::string_view title, uint16_t width, uint16_t height);
    virtual ~MacOSWindow();

    bool shouldClose() override;
    void update() override;
    void *getNative() override;
    WindowProperties getProperties() override;
    glm::vec2 getDimensions() override;

  private:
    virtual void init();
    virtual void destroy();

    GLFWwindow *_window;
    WindowProperties _properties;
  };
}

#endif