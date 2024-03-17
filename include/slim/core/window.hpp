#ifndef SLIM_CORE_WINDOW_HPP_
#define SLIM_CORE_WINDOW_HPP_

#include <cstdint>
#include <glm/ext/vector_int2.hpp>
#include <memory>
#include <string>

namespace slim {
/**
 * \brief The abstract base window interface.
 *
 * This abstract class defines an interface for platform specific window
 * implementations, as well as a \ref create method to instantiate a platform
 * specific window.
 *
 * \ingroup core
 */
class Window {  // NOLINT(cppcoreguidelines-special-member-functions)
public:
  /**
   * \brief The default width of a window.
   */
  static const uint16_t kDefaultWidth = 1920;

  /**
   * \brief The default height of a window.
   */
  static const uint16_t kDefaultHeight = 1080;

  /**
   * \brief The destructor of the Window class.
   */
  virtual ~Window() noexcept = default;

  /**
   * \brief This method instantiates a platform specific window.
   *
   * \param title The title of the window.
   * \param width The width of the window.
   * \param height The height of the window.
   * \param vsync Whether to enable/disable vsync.
   * \param focused Whether to focus the created window.
   * \param minimized Whether to minimize the created window.
   *
   * \return An `std::unique_ptr<Window>`, pointing to the created Window.
   */
  [[nodiscard]] static auto create(const std::string &title, uint16_t width,
                                   uint16_t height, bool vsync, bool focused,
                                   bool minimized) noexcept
      -> std::unique_ptr<Window>;

  /**
   * \name Interface Methods
   *
   * Virtual methods that require implementation.
   */
  ///@{
  virtual auto update() const noexcept -> void = 0;
  virtual auto close() const noexcept -> void = 0;
  [[nodiscard]] virtual auto isOpen() const noexcept -> bool = 0;

  virtual auto setTitle(const std::string &title) noexcept -> void = 0;
  [[nodiscard]] virtual auto getTitle() const noexcept
      -> const std::string & = 0;

  virtual auto setDimensions(const glm::ivec2 &dimensions) noexcept -> void = 0;
  [[nodiscard]] virtual auto getDimensions() const noexcept -> glm::ivec2 = 0;

  virtual auto setWidth(uint16_t width) noexcept -> void = 0;
  [[nodiscard]] virtual auto getWidth() const noexcept -> uint16_t = 0;

  virtual auto setHeight(uint16_t height) noexcept -> void = 0;
  [[nodiscard]] virtual auto getHeight() const noexcept -> uint16_t = 0;

  virtual auto setVsync(bool value) noexcept -> void = 0;
  [[nodiscard]] virtual auto getVsync() const noexcept -> bool = 0;

  virtual auto setFocus(bool value) noexcept -> void = 0;
  [[nodiscard]] virtual auto isFocused() const noexcept -> bool = 0;

  virtual auto setMinimize(bool value) noexcept -> void = 0;
  [[nodiscard]] virtual auto isMinimized() const noexcept -> bool = 0;
  ///@}

protected:
  Window() = default;
};
}  // namespace slim

#endif  // SLIM_CORE_WINDOW_HPP_
