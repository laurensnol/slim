#ifndef SLIM_PLATFORM_DESKTOP_WINDOW_H_
#define SLIM_PLATFORM_DESKTOP_WINDOW_H_

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <cstdint>
#include <string>

#include "slim/core/window.hpp"

namespace slim {
class DesktopWindow : public Window {
private:
  struct WindowProperties {
    std::string title;
    uint16_t width;
    uint16_t height;
    bool vsync;
    bool focused;
    bool minimized;
  };

public:
  DesktopWindow(std::string title, uint16_t width, uint16_t height, bool vsync,
                bool focused, bool minimized) noexcept;
  DesktopWindow(const DesktopWindow &) = delete;
  DesktopWindow(DesktopWindow &&) = delete;
  auto operator=(const DesktopWindow &) -> DesktopWindow & = delete;
  auto operator=(DesktopWindow &&) -> DesktopWindow & = delete;
  ~DesktopWindow() noexcept override;

  auto update() const noexcept -> void override;
  auto close() const noexcept -> void override;
  [[nodiscard]] auto isOpen() const noexcept -> bool override;

  auto setTitle(const std::string &title) noexcept -> void override;
  [[nodiscard]] auto getTitle() const noexcept -> const std::string & override;

  auto setDimensions(uint16_t width, uint16_t height) noexcept -> void override;

  auto setWidth(uint16_t width) noexcept -> void override;
  [[nodiscard]] auto getWidth() const noexcept -> uint16_t override;

  auto setHeight(uint16_t height) noexcept -> void override;
  [[nodiscard]] auto getHeight() const noexcept -> uint16_t override;

  auto setVsync(bool value) noexcept -> void override;
  [[nodiscard]] auto getVsync() const noexcept -> bool override;

  auto setFocus(bool value) noexcept -> void override;
  [[nodiscard]] auto isFocused() const noexcept -> bool override;

  auto setMinimize(bool value) noexcept -> void override;
  [[nodiscard]] auto isMinimized() const noexcept -> bool override;

private:
  GLFWwindow *window_;
  WindowProperties properties_;

  static auto glfwCloseCallback(GLFWwindow *window) noexcept -> void;
  static auto glfwFramebufferSizeCallback(GLFWwindow *window, int width,
                                          int height) noexcept -> void;
  static auto glfwWindowFocusCallback(GLFWwindow *window, int focused) noexcept
      -> void;
  static auto glfwWindowIconifyCallback(GLFWwindow *window,
                                        int iconified) noexcept -> void;
  static auto glfwKeyCallback(GLFWwindow *window, int key, int scancode,
                              int action, int mods) noexcept -> void;
  static auto glfwMouseButtonCallback(GLFWwindow *window, int button,
                                      int action, int mods) noexcept -> void;
  static auto glfwCursorPosCallback(GLFWwindow *window, double xpos,
                                    double ypos) noexcept -> void;
};
}  // namespace slim

#endif  // SLIM_PLATFORM_DESKTOP_WINDOW_H_
