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
    MacOSWindow(std::string_view title, uint16_t width, uint16_t height, bool vsync);
    virtual ~MacOSWindow();

    bool shouldClose() override;
    void update() override;
    void* getNative() const override;

    WindowProperties getProperties() const override;
    glm::vec2 getDimensions() const override;

    void setDimensions(glm::vec2 size) override;
    void setWidth(float width) override;
    void setHeight(float height) override;

    bool getVsync() const override;
    void setVsync(bool value) override;

  private:
    virtual void init();
    virtual void destroy();

    GLFWwindow* m_window;
    WindowProperties m_properties;

    // GLFW callbacks
    static void glfwErrorCallback(int error, const char* description);
    static void glfwWindowCloseCallback(GLFWwindow* window);
    static void glfwFramebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void glfwWindowFocusCallback(GLFWwindow* window, int focused);
    static void glfwWindowIconifyCallback(GLFWwindow* window, int iconified);
  };
}

#endif