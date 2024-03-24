#include "slim/platform/opengl/opengl_renderer_provider.hpp"

// IWYU pragma: no_include "glm/detail/qualifier.hpp"

#include <glad/gl.h>

#include <glm/ext/vector_float4.hpp>

#include "slim/core/application.hpp"
#include "slim/core/window.hpp"
#include "slim/events/window_events.hpp"
#include "slim/renderer/renderer.hpp"

namespace slim {
OpenGLRendererProvider::OpenGLRendererProvider() noexcept {
  auto dimensions = Application::getWindow().getDimensions();
  glViewport(0, 0, dimensions.x, dimensions.y);
}

auto constexpr OpenGLRendererProvider::getAPI() const noexcept
    -> Renderer::API {
  return Renderer::API::OpenGL;
}

auto OpenGLRendererProvider::setClearColor(const glm::vec4& color) -> void {
  glClearColor(color.r, color.g, color.b, color.a);
}

auto OpenGLRendererProvider::clear() const noexcept -> void {
  glClear(GL_COLOR_BUFFER_BIT);
}

auto OpenGLRendererProvider::draw() const noexcept -> void {}

auto OpenGLRendererProvider::onEvent(const WindowResizeEvent& event) noexcept
    -> void {
  auto dimensions = event.getDimensions();
  glViewport(0, 0, dimensions.x, dimensions.y);
}
}  // namespace slim
