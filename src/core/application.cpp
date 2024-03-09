#include "slim/core/application.hpp"

#include <glad/gl.h>

#include <cassert>
#include <cstdint>
#include <memory>
#include <string>

#include "slim/core/window.hpp"

namespace slim {

bool Application::running_ = true;
std::unique_ptr<Window> Application::window_ = nullptr;

Application::~Application() noexcept { terminate(); }

auto Application::init(const std::string& title, uint16_t width,
                       uint16_t height, bool vsync, bool focused,
                       bool minimized) noexcept -> void {
  window_ = Window::create(title, width, height, vsync, focused, minimized);
  // TODO(laurensnol): Call Renderer::init(...) with framebuffer (!) sizes
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

auto Application::terminate() noexcept -> void {
  running_ = false;
  shutdown();
}

auto Application::shutdown() noexcept -> void {}

auto Application::getWindow() noexcept -> const Window& {
  assert(window_);
  return *window_;
}
}  // namespace slim
