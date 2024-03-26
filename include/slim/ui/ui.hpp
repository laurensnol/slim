#ifndef SLIM_UI_UI_HPP_
#define SLIM_UI_UI_HPP_

namespace slim {
class UI final {
public:
#if defined(SLIM_PLATFORM_WINDOWS) || defined(SLIM_PLATFORM_LINUX) || \
    defined(SLIM_PLATFORM_MACOS)
  static auto init() noexcept -> void;
  static auto shutdown() noexcept -> void;
#endif

  static auto drawBegin() noexcept -> void;
  static auto drawEnd() noexcept -> void;

  static auto capturesMouse() noexcept -> bool;
  static auto capturesKeyboard() noexcept -> bool;
};
}  // namespace slim

#endif  // SLIM_UI_UI_HPP_
