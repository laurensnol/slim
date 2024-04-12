#ifndef SLIM_CORE_APPLICATION_HPP_
#define SLIM_CORE_APPLICATION_HPP_

#include <cstdint>
#include <memory>
#include <string>

#include "slim/core/window.hpp"
#include "slim/events/event_handler.hpp"
#include "slim/events/window_events.hpp" // IWYU pragma: keep

namespace slim {
/**
 * \brief The main slim application.
 *
 * \ingroup core
 */
class Application : public EventHandler<WindowCloseEvent> {
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
  ~Application() noexcept override;

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

  /**
   * \brief Implements \ref EventHandler<WindowCloseEvent>.
   */
  auto onEvent(const WindowCloseEvent &event) noexcept -> void override;

private:
  Application() noexcept;

  static auto shutdown() noexcept -> void;

  inline static bool running_ = false;
  inline static std::unique_ptr<Application> instance_ = nullptr;
  inline static std::unique_ptr<Window> window_ = nullptr;
};
}  // namespace slim

#endif  // SLIM_CORE_APPLICATION_HPP_
