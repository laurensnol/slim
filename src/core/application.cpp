#include "slim/core/application.hpp"

#include <glad/gl.h>

#include <cassert>
#include <cstdint>
#include <exception>
#include <iostream>
#include <memory>
#include <new>
#include <string>

#include "slim/core/window.hpp"
#include "slim/events/window_events.hpp"

namespace slim {

Application::~Application() noexcept { terminate(); }

auto Application::init(const std::string& title, uint16_t width,
                       uint16_t height, bool vsync, bool focused,
                       bool minimized) noexcept -> void {
  window_ = Window::create(title, width, height, vsync, focused, minimized);
  // TODO(laurensnol): Call Renderer::init(...) with framebuffer (!) sizes

  try {
    instance_ = std::unique_ptr<Application>(new Application());
  } catch (const std::bad_alloc& exception) {
    // TODO(laurensnol): Replace with proper custom assert
    std::cout << "Failed to allocated space for Application.\n";
    std::terminate();
  }
}

auto Application::run() noexcept -> void {
  // TODO(laurensnol): Call Renderer::setClearColor(...)
  const GLfloat rgb = 0.1F;  // NOLINT
  glClearColor(rgb, rgb, rgb, 1.0);

  while (running_) {
    // TODO(laurensnol): Call Renderer::clear()
    glClear(GL_COLOR_BUFFER_BIT);
    window_->update();
  }
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
}  // namespace slim
