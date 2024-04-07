#include "slim/input/input.hpp"

// IWYU pragma: no_include <glm/detail/qualifier.hpp>

#include <glm/ext/vector_float2.hpp>
#include <memory>

#include "slim/core/assert.hpp"
#include "slim/input/codes.hpp"  // IWYU pragma: keep
#include "slim/input/input_provider.hpp"
#include "slim/platform/desktop/desktop_input_provider.hpp"

#if !defined(SLIM_PLATFORM_WINDOWS) && !defined(SLIM_PLATFORM_LINUX) && \
    !defined(SLIM_PLATFORM_MACOS)
#include "slim/core/error.hpp"
#endif

namespace slim {
auto Input::init() noexcept -> void {
  SLIM_CORE_ASSERT(!provider_, "Input already initialized");

#ifdef SLIM_PLATFORM_WINDOWS
  provider_ = std::make_unique<DesktopInputProvider>();
#elif SLIM_PLATFORM_LINUX
  provider_ = std::make_unique<DesktopInputProvider>();
#elif SLIM_PLATFORM_MACOS
  provider_ = std::make_unique<DesktopInputProvider>();
#else
  SLIM_CORE_FATAL_ERROR("SLIM_PLATFORM not defined");
#endif
}

auto Input::isKeyUp(Key key) noexcept -> bool {
  SLIM_CORE_ASSERT(provider_, "Input not initialized");
  return provider_->isKeyUp(key);
}

auto Input::isKeyDown(Key key) noexcept -> bool {
  SLIM_CORE_ASSERT(provider_, "Input not initialized");
  return provider_->isKeyDown(key);
}

auto Input::isMouseButtonUp(MouseButton button) noexcept -> bool {
  SLIM_CORE_ASSERT(provider_, "Input not initialized");
  return provider_->isMouseButtonUp(button);
}

auto Input::isMouseButtonDown(MouseButton button) noexcept -> bool {
  SLIM_CORE_ASSERT(provider_, "Input not initialized");
  return provider_->isMouseButtonDown(button);
}

auto Input::getMousePosition() noexcept -> glm::vec2 {
  SLIM_CORE_ASSERT(provider_, "Input not initialized");
  return provider_->getMousePosition();
}

auto Input::getMouseScroll() noexcept -> glm::vec2 {
  SLIM_CORE_ASSERT(provider_, "Input not initialized");
  return provider_->getMouseScroll();
}
}  // namespace slim
