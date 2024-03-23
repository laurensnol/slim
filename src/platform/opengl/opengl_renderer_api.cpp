#include "slim/platform/opengl/opengl_renderer_api.hpp"

// IWYU pragma: no_include "glm/detail/qualifier.hpp"

#include <glad/gl.h>

#include <glm/ext/vector_float4.hpp>

#include "slim/core/application.hpp"
#include "slim/core/window.hpp"
#include "slim/events/window_events.hpp"
#include "slim/renderer/renderer_api.hpp"  // IWYU pragma: keep

namespace slim {
OpenGLRendererApi::OpenGLRendererApi() noexcept {
  auto dimensions = Application::getWindow().getDimensions();
  glViewport(0, 0, dimensions.x, dimensions.y);
}

constexpr auto OpenGLRendererApi::getApi() const noexcept -> Api {
  return Api::OpenGL;
}

auto OpenGLRendererApi::setClearColor(const glm::vec4& color) -> void {
  glClearColor(color.r, color.g, color.b, color.a);
}

auto OpenGLRendererApi::clear() const noexcept -> void {
  glClear(GL_COLOR_BUFFER_BIT);
}

auto OpenGLRendererApi::draw() const noexcept -> void {}

auto OpenGLRendererApi::onEvent(const WindowResizeEvent& event) noexcept
    -> void {
  auto dimensions = event.getDimensions();
  glViewport(0, 0, dimensions.x, dimensions.y);
}

}  // namespace slim
