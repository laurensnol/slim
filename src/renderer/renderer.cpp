#include "slim/renderer/renderer.hpp"

// IWYU pragma: no_include <__exception/terminate.h>

#include <cassert>
#include <exception>  // IWYU pragma: keep
#include <glm/ext/vector_float4.hpp>
#include <memory>

#include "slim/platform/opengl/opengl_renderer_provider.hpp"
#include "slim/renderer/renderer_provider.hpp"

namespace slim {
std::unique_ptr<RendererProvider> Renderer::provider_ = nullptr;

auto Renderer::init(API api) noexcept -> void {
  assert(!provider_);

  switch (api) {
    case API::OpenGL:
      provider_ = std::make_unique<OpenGLRendererProvider>();
      break;
    default:
      std::terminate();
  }
}

auto Renderer::setClearColor(const glm::vec4 &color) noexcept -> void {
  provider_->setClearColor(color);
}

auto Renderer::clear() noexcept -> void { provider_->clear(); }

auto Renderer::draw() noexcept -> void { provider_->draw(); }

auto Renderer::getAPI() noexcept -> API { return provider_->getAPI(); }
}  // namespace slim
