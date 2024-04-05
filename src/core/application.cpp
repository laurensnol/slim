#include "slim/core/application.hpp"

// IWYU pragma: no_include "glm/detail/qualifier.hpp"
// IWYU pragma: no_include "glm/detail/type_vec4.inl"
// IWYU pragma: no_include "glm/detail/type_vec4.inl"

#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <memory>
#include <new>
#include <string>

#include "slim/core/log.hpp"
#include "slim/core/window.hpp"
#include "slim/events/window_events.hpp"
#include "slim/input/codes.hpp"
#include "slim/input/input.hpp"
#include "slim/renderer/renderer.hpp"
#include "slim/scene/scene_manager.hpp"
#include "slim/ui/ui.hpp"

namespace slim {

Application::~Application() noexcept { terminate(); }

auto Application::init(const std::string& title, uint16_t width,
                       uint16_t height, bool vsync, bool focused,
                       bool minimized) noexcept -> void {
  window_ = Window::create(title, width, height, vsync, focused, minimized);

  Input::init();
  Renderer::init();
  UI::init();

  try {
    instance_ = std::unique_ptr<Application>(new Application());
  } catch (const std::bad_alloc& exception) {
    // TODO(laurensnol): Replace with proper custom assert
    SLIM_CORE_CRITICAL("Failed to allocate space for Application: {}",
                       exception.what());
    std::abort();
  }

  SLIM_CORE_INFO("Initialized slim");
}

auto Application::run() noexcept -> void {
  assert(SceneManager::getSceneCount() > 0);

  Renderer::setClearColor({0.1, 0.1, 0.1, 1.0});  // NOLINT

  while (running_) {
    if (Input::isKeyDown(Key::Escape)) {
      terminate();
    }

    Renderer::clear();
    SceneManager::update();
    Renderer::draw();

    UI::drawBegin();
    SceneManager::uiDraw();
    UI::drawEnd();

    window_->update();
  }

  shutdown();
}

auto Application::terminate() noexcept -> void { running_ = false; }

auto Application::getWindow() noexcept -> Window& {
  assert(window_);
  return *window_;
}

auto Application::onEvent(const WindowCloseEvent& /*event*/) noexcept -> void {
  terminate();
}

Application::Application() noexcept {
  assert(!instance_);
  running_ = true;
}

auto Application::shutdown() noexcept -> void { UI::shutdown(); }
}  // namespace slim
