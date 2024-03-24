#ifndef SLIM_RENDERER_RENDERER_HPP_
#define SLIM_RENDERER_RENDERER_HPP_

#include <glm/ext/vector_float4.hpp>
#include <memory>

namespace slim {
// Forward declaration
class RendererProvider;

/**
 * \brief A temporary Renderer class.
 *
 * \ingroup renderer
 */
class Renderer {
public:
  /**
   * \brief Definitions for supported graphics APIs.
   */
  enum class API {
    OpenGL,
  };

  /**
   * \brief Initializes the Renderer with the given API.
   *
   * This function initializes the Renderer by creating the specified \ref
   * RendererProvider.
   */
  static auto init(API api = API::OpenGL) noexcept -> void;

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
   * \brief Returns the current \ref Api being used.
   *
   * \return The current \ref Api.
   */
  [[nodiscard]] static auto getAPI() noexcept -> API;

private:
  static std::unique_ptr<RendererProvider> provider_;
};
}  // namespace slim

#endif  // SLIM_RENDERER_RENDERER_HPP_
