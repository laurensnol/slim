#include "slim/renderer/renderer.hpp"

// IWYU pragma: no_include <__exception/terminate.h>

#include <cassert>
#include <exception>  // IWYU pragma: keep
#include <glm/ext/vector_float4.hpp>
#include <memory>

#include "slim/platform/opengl/opengl_renderer_api.hpp"
#include "slim/renderer/renderer_api.hpp"

namespace slim {
auto Renderer::init(Api api) noexcept -> void {
  assert(!api_);

  switch (api) {
    case Api::OpenGL:
      api_ = std::make_unique<OpenGLRendererApi>();
      break;
    default:
      std::terminate();
  }
}

auto Renderer::setClearColor(const glm::vec4 &color) noexcept -> void {
  api_->setClearColor(color);
}

auto Renderer::clear() noexcept -> void { api_->clear(); }

auto Renderer::draw() noexcept -> void { api_->draw(); }

auto Renderer::getApi() noexcept -> Api { return api_->getApi(); }
}  // namespace slim
