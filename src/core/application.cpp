#include "slim/core/application.hpp"

// IWYU pragma: no_include "glm/detail/qualifier.hpp"
// IWYU pragma: no_include "glm/detail/type_vec4.inl"
// IWYU pragma: no_include "glm/detail/type_vec4.inl"

#include <cstdint>
#include <memory>
#include <new>
#include <string>

#include "slim/core/assert.hpp"
#include "slim/core/error.hpp"
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
    SLIM_CORE_FATAL_ERROR("Failed to allocate space for Application: {}",
                          exception.what());
  }

  SLIM_CORE_LOG_INFO("Initialized slim");
}

auto Application::run() noexcept -> void {
  SLIM_CORE_ASSERT(SceneManager::getSceneCount() > 0, "No scenes found");

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
  SLIM_CORE_ASSERT(window_, "Window not initialized");
  return *window_;
}

auto Application::onEvent(const WindowCloseEvent& /*event*/) noexcept -> void {
  terminate();
}

Application::Application() noexcept {
  SLIM_CORE_ASSERT(!instance_, "Application not initialized");
  running_ = true;
}

auto Application::shutdown() noexcept -> void { UI::shutdown(); }
}  // namespace slim
