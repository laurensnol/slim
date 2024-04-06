#include "slim/platform/opengl/opengl_renderer_provider.hpp"

// IWYU pragma: no_include "glm/detail/qualifier.hpp"
// IWYU pragma: no_include "glm/detail/type_vec2.inl"

#include <glad/gl.h>

#include <glm/ext/vector_float4.hpp>
#include <glm/ext/vector_int2.hpp>

#include "slim/core/application.hpp"
#include "slim/core/window.hpp"
#include "slim/renderer/renderer.hpp"

namespace slim {
OpenGLRendererProvider::OpenGLRendererProvider() noexcept
    : viewport_({0, 0}, Application::getWindow().getFramebufferDimensions()) {
  glViewport(viewport_.position.x, viewport_.position.y, viewport_.dimensions.x,
             viewport_.dimensions.y);
}

auto constexpr OpenGLRendererProvider::getAPI() const noexcept
    -> Renderer::API {
  return Renderer::API::OpenGL;
}

auto OpenGLRendererProvider::setClearColor(const glm::vec4& color) noexcept
    -> void {
  glClearColor(color.r, color.g, color.b, color.a);
}

auto OpenGLRendererProvider::setViewport(const glm::ivec2& position,
                                         const glm::ivec2& dimensions) noexcept
    -> void {
  viewport_.position = position;
  viewport_.dimensions = dimensions;
  glViewport(viewport_.position.x, viewport_.position.y, viewport_.dimensions.x,
             viewport_.dimensions.y);
}

auto OpenGLRendererProvider::getViewport() const noexcept
    -> const Renderer::Viewport& {
  return viewport_;
}

auto OpenGLRendererProvider::clear() const noexcept -> void {
  glClear(GL_COLOR_BUFFER_BIT);
}

auto OpenGLRendererProvider::draw() const noexcept -> void {}
}  // namespace slim
