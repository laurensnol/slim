#include "core/input.h"
#include "core/application.h"
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

namespace slim
{
  glm::vec2 Input::mousePosition = {0.0f, 0.0f};
  glm::vec2 Input::mouseDelta = {0.0f, 0.0f};
  glm::vec2 Input::mouseScroll = {0.0f, 0.0f};
  glm::vec2 Input::s_lastMousePosition = {0.0f, 0.0f};
  void* Input::s_nativeWindowPtr = nullptr;

  void Input::init()
  {
    s_nativeWindowPtr = Application::getInstance().getWindow().getNative();
    GLFWwindow* window = static_cast<GLFWwindow*>(s_nativeWindowPtr);

    glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset){
      mouseScroll = glm::vec2(xoffset, yoffset);
    });
  }

  void Input::onUpdate()
  {
    GLFWwindow* window = static_cast<GLFWwindow*>(s_nativeWindowPtr);
    
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);
    mousePosition = glm::vec2(mouseX, mouseY);
    mouseDelta = s_lastMousePosition - mousePosition;
    s_lastMousePosition = mousePosition;
  }

  bool Input::getKeyDown(Key key)
  {
    GLFWwindow* window = static_cast<GLFWwindow*>(s_nativeWindowPtr);
    return glfwGetKey(window, static_cast<int32_t>(key)) == GLFW_PRESS;
  }

  bool Input::getMouseDown(MouseButton mouseButton)
  {
    GLFWwindow* window = static_cast<GLFWwindow*>(s_nativeWindowPtr);
    return glfwGetMouseButton(window, static_cast<int32_t>(mouseButton)) == GLFW_PRESS;
  }
}