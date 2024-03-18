#ifndef SLIM_PLATFORM_DESKTOP_WINDOW_HPP_
#define SLIM_PLATFORM_DESKTOP_WINDOW_HPP_

#include <GLFW/glfw3.h>

#include <cstdint>
#include <glm/ext/vector_int2.hpp>
#include <string>

#include "slim/core/window.hpp"
#include "slim/platform/desktop_input_provider.hpp"  // IWYU pragma: keep

namespace slim {
/**
 * \brief A Window implementation for desktop platforms.
 *
 * This class implements the \ref Window interface with a concrete
 * implementation for a window on desktop platforms.
 *
 * Most `set` methods will update the window by calling the corresponding GLFW
 * methods. The properties will then get updated by the corresponding callback
 * that's being called by GLFW.
 *
 * \ingroup platform
 */
class DesktopWindow : public Window {
  friend DesktopInputProvider;

  // Will be used as GLFW's user pointer.
  struct WindowProperties {
    std::string title;
    uint16_t width;
    uint16_t height;
    bool vsync;
    bool focused;
    bool minimized;
  };

public:
  /**
   * \brief The constructor of a DesktopWindow.
   *
   * The constructor will initialize GLFW, set necessary window hints, create
   * the GLFWwindow, set callbacks and create an OpenGL context.
   *
   * \param title The title of the window.
   * \param width The width of the window.
   * \param height The height of the window.
   * \param vsync Whether to enable VSync.
   * \param focused Whether the window is focused after creation.
   * \param minimized Whether the window is minimized after creation.
   *
   * \see https://www.glfw.org/docs/3.4/window_guide.html#window_creation
   */
  DesktopWindow(std::string title, uint16_t width, uint16_t height, bool vsync,
                bool focused, bool minimized) noexcept;

  /**
   * \name Deleted copy/move constructors & assignment operators.
   */
  ///@{
  DesktopWindow(const DesktopWindow &) = delete;
  DesktopWindow(DesktopWindow &&) = delete;
  auto operator=(const DesktopWindow &) -> DesktopWindow & = delete;
  auto operator=(DesktopWindow &&) -> DesktopWindow & = delete;
  ///@}

  /**
   * \brief The destructor of a DesktopWindow.
   *
   * This will destroy the window and shutdown GLFW.
   *
   * \see https://www.glfw.org/docs/3.4/window_guide.html#window_destruction
   */
  ~DesktopWindow() noexcept override;

  /**
   * \brief This method updates the window and polls events.
   *
   * This method will update the window by swapping it's buffers and poll
   * events.
   *
   * \see https://www.glfw.org/docs/3.4/input_guide.html#events
   * \see https://www.glfw.org/docs/3.4/window_guide.html#buffer_swap
   */
  auto update() const noexcept -> void override;

  /**
   * \brief Close the window.
   *
   * This window will set the window's close flag to `true`.
   *
   * \see https://www.glfw.org/docs/3.4/window_guide.html#window_close
   */
  auto close() const noexcept -> void override;

  /**
   * \brief Returns whether the window is currently open.
   *
   * This method returns `true` if the window's close flag is set to `false`,
   * otherwise `false`.
   *
   * \return A `bool` whether the window is open or not.
   *
   * \see https://www.glfw.org/docs/3.4/window_guide.html#window_close
   */
  [[nodiscard]] auto isOpen() const noexcept -> bool override;

  /**
   * \brief Sets the title of the window.
   *
   * \param title The new title.
   *
   * \see https://www.glfw.org/docs/3.4/window_guide.html#window_title
   */
  auto setTitle(const std::string &title) noexcept -> void override;

  /**
   * \brief Returns the current title of the window.
   *
   * \return The current title of the window.
   *
   * \see https://www.glfw.org/docs/3.4/window_guide.html#window_title
   */
  [[nodiscard]] auto getTitle() const noexcept -> const std::string & override;

  /**
   * \brief Sets the width and height of the window.
   *
   * \param width The new width of the window.
   * \param height The new height of the window.
   *
   * \see https://www.glfw.org/docs/3.4/window_guide.html#window_size
   */
  auto setDimensions(const glm::ivec2 &dimensions) noexcept -> void override;

  /**
   * \brief Returns the Window's dimensions.
   *
   * \return The dimensions as a \ref glm::vec2.
   *
   * \see https://www.glfw.org/docs/3.3/window_guide.html#window_size
   */
  [[nodiscard]] auto getDimensions() const noexcept -> glm::ivec2 override;

  /**
   * \brief Sets the width of the window.
   *
   * \param width The new width of the window.
   *
   * \see https://www.glfw.org/docs/3.4/window_guide.html#window_size
   */
  auto setWidth(uint16_t width) noexcept -> void override;

  /**
   * \brief Returns the current width of the window.
   *
   * \return The current width of the window.
   *
   * \see https://www.glfw.org/docs/3.4/window_guide.html#window_size
   */
  [[nodiscard]] auto getWidth() const noexcept -> uint16_t override;

  /**
   * \brief Sets the width of the window.
   *
   * \param width The new width of the window.
   *
   * \see https://www.glfw.org/docs/3.4/window_guide.html#window_size
   */
  auto setHeight(uint16_t height) noexcept -> void override;

  /**
   * \brief Returns the current height of the window.
   *
   * \return The current height of the window.
   *
   * \see https://www.glfw.org/docs/3.4/window_guide.html#window_size
   */
  [[nodiscard]] auto getHeight() const noexcept -> uint16_t override;

  /**
   * \brief Enables or disables VSync.
   *
   * \param value Whether to enable or disable VSync.
   *
   * \see https://www.glfw.org/docs/3.4/window_guide.html#buffer_swap
   */
  auto setVsync(bool value) noexcept -> void override;

  /**
   * \brief Returns whether VSync is enabled or not.
   *
   * \return `true` if VSync is enabled, `false` if not.
   *
   * \see https://www.glfw.org/docs/3.4/window_guide.html#buffer_swap
   */
  [[nodiscard]] auto getVsync() const noexcept -> bool override;

  /**
   * \brief Sets the focus of the window.
   *
   * \param value Whether the window should be focused or not.
   *
   * \see https://www.glfw.org/docs/3.4/window_guide.html#window_focus
   */
  auto setFocus(bool value) noexcept -> void override;

  /**
   * \brief Whether the window is focused or not.
   *
   * \return `true` if focused, `false` if not.
   *
   * \see https://www.glfw.org/docs/3.4/window_guide.html#window_focus
   */
  [[nodiscard]] auto isFocused() const noexcept -> bool override;

  /**
   * \brief Minimizes or maximizes the window.
   *
   * \param value Whether to minimize the window (`true`) or not (`false`).
   *
   * \see https://www.glfw.org/docs/3.4/window_guide.html#window_iconify
   */
  auto setMinimize(bool value) noexcept -> void override;

  /**
   * \brief Whether the window is minimized or not.
   *
   * \return `true` if minimized, `false` if not.
   *
   * \see https://www.glfw.org/docs/3.4/window_guide.html#window_iconify
   */
  [[nodiscard]] auto isMinimized() const noexcept -> bool override;

private:
  GLFWwindow *window_;
  WindowProperties properties_;

  // GLFW callbacks

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

#endif  // SLIM_PLATFORM_DESKTOP_WINDOW_HPP_
