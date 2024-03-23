#ifndef SLIM_PLATFORM_OPENGL_RENDERER_API_HPP_
#define SLIM_PLATFORM_OPENGL_RENDERER_API_HPP_

#include <glm/ext/vector_float4.hpp>

#include "slim/events/event_handler.hpp"
#include "slim/events/window_events.hpp"
#include "slim/renderer/renderer_api.hpp"

namespace slim {
class OpenGLRendererApi : public RendererApi, EventHandler<WindowResizeEvent> {
public:
  OpenGLRendererApi() noexcept;

  [[nodiscard]] constexpr auto getApi() const noexcept -> Api override;

  auto setClearColor(const glm::vec4& color) -> void override;
  auto clear() const noexcept -> void override;
  auto draw() const noexcept -> void override;

  auto onEvent(const WindowResizeEvent& event) noexcept -> void override;
};
}  // namespace slim

#endif  // SLIM_PLATFORM_OPENGL_RENDERER_API_HPP_
