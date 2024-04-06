#include "slim/renderer/renderer.hpp"

#include <glm/ext/vector_float4.hpp>
#include <glm/ext/vector_int2.hpp>
#include <memory>

#include "slim/core/assert.hpp"
#include "slim/core/error.hpp"
#include "slim/platform/opengl/opengl_renderer_provider.hpp"
#include "slim/renderer/renderer_provider.hpp"

namespace slim {
std::unique_ptr<RendererProvider> Renderer::provider_ = nullptr;

auto Renderer::init(API api) noexcept -> void {
  SLIM_CORE_ASSERT(!provider_, "Renderer already initialized");

  switch (api) {
    case API::OpenGL:
      provider_ = std::make_unique<OpenGLRendererProvider>();
      break;
    default:
      SLIM_CORE_FATAL_ERROR("Invalid Renderer::API");
  }
}

auto Renderer::setClearColor(const glm::vec4 &color) noexcept -> void {
  SLIM_CORE_ASSERT(provider_, "Renderer not initalized");
  provider_->setClearColor(color);
}

auto Renderer::setViewport(const glm::ivec2 &position,
                           const glm::ivec2 &dimensions) noexcept -> void {
  SLIM_CORE_ASSERT(provider_, "Renderer not initalized");
  provider_->setViewport(position, dimensions);
}

auto Renderer::getViewport() noexcept -> const Viewport & {
  SLIM_CORE_ASSERT(provider_, "Renderer not initalized");
  return provider_->getViewport();
}

auto Renderer::clear() noexcept -> void {
  SLIM_CORE_ASSERT(provider_, "Renderer not initalized");
  provider_->clear();
}

auto Renderer::draw() noexcept -> void {
  SLIM_CORE_ASSERT(provider_, "Renderer not initalized");
  provider_->draw();
}

auto Renderer::getAPI() noexcept -> API {
  SLIM_CORE_ASSERT(provider_, "Renderer not initalized");
  return provider_->getAPI();
}
}  // namespace slim
