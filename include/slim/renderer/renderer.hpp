#ifndef SLIM_RENDERER_RENDERER_HPP_
#define SLIM_RENDERER_RENDERER_HPP_

#include <glm/ext/vector_float4.hpp>
#include <memory>

#include "slim/renderer/renderer_api.hpp"

namespace slim {
/**
 * \brief A temporary Renderer class.
 *
 * \ingroup renderer
 */
class Renderer {
  using Api = RendererApi::Api;

public:
  /**
   * \brief Initializes the Renderer with the given API.
   *
   * This function initializes the Renderer by creating the specified \ref
   * RendererApi.
   */
  static auto init(Api api = Api::OpenGL) noexcept -> void;

  /**
   * \brief Sets the clear color.
   */
  static auto setClearColor(const glm::vec4& color) noexcept -> void;

  /**
   * \brief Clears the screen.
   */
  static auto clear() noexcept -> void;

  /**
   * \brief TODO(laurensnol): Lets find out what to do here.
   */
  static auto draw() noexcept -> void;

  /**
   * \brief Returns the current \ref RendererApi::Api being used.
   *
   * \return The current \ref RendererApi::Api.
   */
  [[nodiscard]] static auto getApi() noexcept -> Api;

private:
  inline static std::unique_ptr<RendererApi> api_ = nullptr;
};
}  // namespace slim

#endif  // SLIM_RENDERER_RENDERER_HPP_
