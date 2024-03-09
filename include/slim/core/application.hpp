#ifndef SLIM_CORE_APPLICATION_H_
#define SLIM_CORE_APPLICATION_H_

#include <cstdint>
#include <memory>
#include <string>

// Forward declaration
namespace slim {
class Window;
}

namespace slim {
class Application final {
public:
  static const uint16_t kDefaultWidth = 1920;
  static const uint16_t kDefaultHeight = 1080;

  Application(const Application &) = delete;
  Application(Application &&) = delete;
  auto operator=(const Application &) -> Application & = delete;
  auto operator=(Application &&) -> Application & = delete;
  ~Application() noexcept;

  static auto init(const std::string &title = "slim",
                   uint16_t width = kDefaultWidth,
                   uint16_t height = kDefaultHeight, bool vsync = true,
                   bool focused = true, bool minimized = false) noexcept
      -> void;
  static auto run() noexcept -> void;
  static auto terminate() noexcept -> void;
  [[nodiscard]] static auto getWindow() noexcept -> Window &;

private:
  static auto shutdown() noexcept -> void;

  static bool running_;
  static std::unique_ptr<Window> window_;
};
}  // namespace slim

#endif  // SLIM_CORE_APPLICATION_H_
