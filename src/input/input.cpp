#include "slim/input/input.hpp"

// IWYU pragma: no_include "glm/detail/qualifier.hpp"

#include <glm/ext/vector_float2.hpp>
#include <memory>

#include "slim/input/codes.hpp"  // IWYU pragma: keep
#include "slim/input/input_provider.hpp"
#include "slim/platform/desktop_input_provider.hpp"

namespace slim {
auto Input::init() noexcept -> void {
#ifdef SLIM_PLATFORM_WINDOWS
  provider_ = std::make_unique<DesktopInputProvider>();
#elif SLIM_PLATFORM_LINUX
  provider_ = std::make_unique<DesktopInputProvider>();
#elif SLIM_PLATFORM_MACOS
  provider_ = std::make_unique<DesktopInputProvider>();
#else
  // NOLINTNEXTLINE
  static_assert(false, "SLIM_PLATFORM not defined");
#endif
}

auto Input::isKeyUp(Key key) noexcept -> bool {
  return provider_->isKeyUp(key);
}

auto Input::isKeyDown(Key key) noexcept -> bool {
  return provider_->isKeyDown(key);
}

auto Input::isMouseButtonUp(MouseButton button) noexcept -> bool {
  return provider_->isMouseButtonUp(button);
}

auto Input::isMouseButtonDown(MouseButton button) noexcept -> bool {
  return provider_->isMouseButtonDown(button);
}

auto Input::getMousePosition() noexcept -> glm::vec2 {
  return provider_->getMousePosition();
}

auto Input::getMouseScroll() noexcept -> glm::vec2 {
  return provider_->getMouseScroll();
}
}  // namespace slim
