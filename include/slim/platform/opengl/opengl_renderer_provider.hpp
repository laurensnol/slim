#ifndef SLIM_PLATFORM_OPENGL_RENDERER_PROVIDER_HPP_
#define SLIM_PLATFORM_OPENGL_RENDERER_PROVIDER_HPP_

#include <glm/ext/vector_float4.hpp>

#include "slim/events/event_handler.hpp"
#include "slim/events/window_events.hpp"
#include "slim/renderer/renderer.hpp"
#include "slim/renderer/renderer_provider.hpp"

namespace slim {
/**
 * \brief Implements \ref RendererProvider for the OpenGL graphics API.
 *
 * \ingroup platform
 */
class OpenGLRendererProvider : public RendererProvider,
                               EventHandler<WindowResizeEvent> {
public:
  OpenGLRendererProvider() noexcept;

  [[nodiscard]] constexpr auto getApi() const noexcept
      -> Renderer::Api override;

  auto setClearColor(const glm::vec4& color) -> void override;
  auto clear() const noexcept -> void override;
  auto draw() const noexcept -> void override;

  auto onEvent(const WindowResizeEvent& event) noexcept -> void override;
};
}  // namespace slim

#endif  // SLIM_PLATFORM_OPENGL_RENDERER_PROVIDER_HPP_
