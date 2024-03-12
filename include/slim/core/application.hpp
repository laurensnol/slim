#ifndef SLIM_CORE_APPLICATION_H_
#define SLIM_CORE_APPLICATION_H_

#include <cstdint>
#include <memory>
#include <string>

#include "slim/core/window.hpp"

namespace slim {
/**
 * \brief The main slim application.
 *
 * \ingroup core
 */
class Application final {
public:
  /**
   * \name Deleted copy/move constructors & assignment operators.
   */
  ///@{
  Application(const Application &) = delete;
  Application(Application &&) = delete;
  auto operator=(const Application &) -> Application & = delete;
  auto operator=(Application &&) -> Application & = delete;
  ///@}

  /**
   * \brief The destructor of the Application class.
   */
  ~Application() noexcept;

  /**
   * \brief Initializes a slim application.
   *
   * This method initializes the slim application, window and subsystems. It
   * should be called before using any other slim features.
   *
   * \param title The title of the application/window.
   * \param width The width of the window.
   * \param height The height of the window.
   * \param vsync Whether to enable/disable vsync.
   * \param focused Whether to focus the created window.
   * \param minimized Whether to minimize the created window.
   */
  static auto init(const std::string &title = "slim",
                   uint16_t width = Window::kDefaultWidth,
                   uint16_t height = Window::kDefaultHeight, bool vsync = true,
                   bool focused = true, bool minimized = false) noexcept
      -> void;

  /**
   * \brief Starts the Application's main loop.
   */
  static auto run() noexcept -> void;

  /**
   * \brief Stops the Application and shuts down all subsystems.
   */
  static auto terminate() noexcept -> void;

  /**
   * \brief Returns a reference to the main \ref Window.
   */
  [[nodiscard]] static auto getWindow() noexcept -> Window &;

private:
  static auto shutdown() noexcept -> void;

  static bool running_;
  static std::unique_ptr<Window> window_;
};
}  // namespace slim

#endif  // SLIM_CORE_APPLICATION_H_
