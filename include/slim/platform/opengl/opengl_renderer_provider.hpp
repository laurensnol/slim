#ifndef SLIM_PLATFORM_OPENGL_RENDERER_PROVIDER_HPP_
#define SLIM_PLATFORM_OPENGL_RENDERER_PROVIDER_HPP_

#include <glm/ext/vector_float4.hpp>
#include <glm/ext/vector_int2.hpp>

#include "slim/renderer/renderer.hpp"
#include "slim/renderer/renderer_provider.hpp"

namespace slim {
/**
 * \brief Implements \ref RendererProvider for the OpenGL graphics API.
 *
 * \ingroup platform
 */
class OpenGLRendererProvider : public RendererProvider {
public:
  OpenGLRendererProvider() noexcept;

  [[nodiscard]] constexpr auto getAPI() const noexcept
      -> Renderer::API override;

  auto setClearColor(const glm::vec4& color) noexcept -> void override;
  auto setViewport(const glm::ivec2& position,
                   const glm::ivec2& dimensions) noexcept -> void override;
  [[nodiscard]] auto getViewport() const noexcept
      -> const Renderer::Viewport& override;
  auto clear() const noexcept -> void override;
  auto draw() const noexcept -> void override;

private:
  Renderer::Viewport viewport_;
};
}  // namespace slim

#endif  // SLIM_PLATFORM_OPENGL_RENDERER_PROVIDER_HPP_
