#ifndef SLIM_RENDERER_RENDERER_PROVIDER_HPP_
#define SLIM_RENDERER_RENDERER_PROVIDER_HPP_

#include <glm/ext/vector_float4.hpp>

#include "slim/renderer/renderer.hpp"

namespace slim {
/**
 * \brief The abstract base renderer provider interface.
 *
 * This class defines an interface for implementing common renderering calls for
 * a graphics API.
 *
 * \ingroup renderer
 */
class RendererProvider {  // NOLINT(cppcoreguidelines-special-member-functions
public:
  virtual ~RendererProvider() = default;

  /**
   * \name Interface methods.
   *
   * Virtual methods that require implementation.
   */
  ///@{
  [[nodiscard]] constexpr virtual auto getApi() const noexcept
      -> Renderer::Api = 0;

  virtual auto setClearColor(const glm::vec4& color) -> void = 0;
  virtual auto clear() const noexcept -> void = 0;
  virtual auto draw() const noexcept -> void = 0;
  ///@}
};
}  // namespace slim

#endif  // SLIM_RENDERER_RENDERER_PROVIDER_HPP_
