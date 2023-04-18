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
  glm::vec2 Input::s_mouseScrollSum = {0.0f, 0.0f};
  void* Input::s_nativeWindowPtr = nullptr;
  ImGuiIO* Input::s_imguiIo = nullptr;

  void Input::init()
  {
    s_nativeWindowPtr = Application::getInstance().getWindow().getNative();
    GLFWwindow* window = static_cast<GLFWwindow*>(s_nativeWindowPtr);

    glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset){
      s_mouseScrollSum += glm::vec2(xoffset, yoffset);
    });

    s_imguiIo = &ImGui::GetIO();
  }

  void Input::onUpdate()
  {
    GLFWwindow* window = static_cast<GLFWwindow*>(s_nativeWindowPtr);
    
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);
    mousePosition = glm::vec2(mouseX, mouseY);
    mouseDelta = s_lastMousePosition - mousePosition;
    s_lastMousePosition = mousePosition;

    mouseScroll = s_mouseScrollSum;
    s_mouseScrollSum = {0.0f, 0.0f};
  }

  bool Input::getKeyDown(Key key)
  {
    if (s_imguiIo->WantCaptureKeyboard)
      return false;

    GLFWwindow* window = static_cast<GLFWwindow*>(s_nativeWindowPtr);
    return glfwGetKey(window, static_cast<int32_t>(key)) == GLFW_PRESS;
  }

  bool Input::getMouseDown(MouseButton mouseButton)
  {
    if (s_imguiIo->WantCaptureMouse)
      return false;

    GLFWwindow* window = static_cast<GLFWwindow*>(s_nativeWindowPtr);
    return glfwGetMouseButton(window, static_cast<int32_t>(mouseButton)) == GLFW_PRESS;
  }
}