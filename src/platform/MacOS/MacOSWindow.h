#ifndef SLIM_MACOSWINDOW
#define SLIM_MACOSWINDOW

#include "core/window.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace slim
{
  class MacOSWindow : public Window
  {
  public:
    MacOSWindow(const WindowProperties &properties);
    virtual ~MacOSWindow();

    bool shouldClose() override;
    void update() override;
    void *getNative() override;
    WindowProperties getProperties() override;

  private:
    virtual void init(const WindowProperties &properties);
    virtual void destroy();

    GLFWwindow *_window;
    WindowProperties _properties;
  };
}

#endif