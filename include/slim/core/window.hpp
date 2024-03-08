#ifndef SLIM_CORE_WINDOW_H_
#define SLIM_CORE_WINDOW_H_

#include <cstdint>
#include <memory>
#include <string>

namespace slim {
class Window {
public:
  static const uint16_t kDefaultWidth = 1920;
  static const uint16_t kDefaultHeight = 1080;

  Window(const Window &) = delete;
  Window(Window &&) = delete;
  auto operator=(const Window &) -> Window & = delete;
  auto operator=(Window &&) -> Window & = delete;
  virtual ~Window() noexcept = default;

  static auto create(const std::string &title, uint16_t width = kDefaultWidth,
                     uint16_t height = kDefaultHeight, bool vsync = true,
                     bool focused = true, bool minimized = false) noexcept
      -> std::unique_ptr<Window>;

  virtual auto update() const noexcept -> void = 0;
  virtual auto close() const noexcept -> void = 0;
  [[nodiscard]] virtual auto isOpen() const noexcept -> bool = 0;

  virtual auto setTitle(const std::string &title) noexcept -> void = 0;
  [[nodiscard]] virtual auto getTitle() const noexcept
      -> const std::string & = 0;

  virtual auto setDimensions(uint16_t width, uint16_t height) noexcept
      -> void = 0;

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

protected:
  explicit Window() = default;
};
}  // namespace slim

#endif  // SLIM_CORE_WINDOW_H_
