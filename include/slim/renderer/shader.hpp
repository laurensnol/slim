#ifndef SLIM_RENDERER_SHADER_HPP_
#define SLIM_RENDERER_SHADER_HPP_

// IWYU pragma: no_include <__fwd/string_view.h>

#include <cstdint>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <memory>
#include <string_view>  // IWYU pragma: keep

namespace slim {
/**
 * \brief The abstract base shader interface.
 *
 * This class defines an interface for a graphics API specific shader
 * implementation.
 *
 * \ingroup renderer
 */
class Shader {  // NOLINT(cppcoreguidelines-special-member-functions)
public:
  virtual ~Shader() noexcept = default;

  /**
   * \brief Creates a new Shader with the given vertex and fragment shaders.
   *
   * This method creates a new \ref std::unique_ptr to a Shader based on \ref
   * Renderer::getAPI.
   *
   * \param vertexShaderPath The absolute path of the vertex shader.
   * \param fragmentShaderPath The absolute path of the fragment shader.
   *
   * \return An \ref std::unique_ptr to the created shader.
   */
  static auto create(std::string_view vertexShaderPath,
                     std::string_view fragmentShaderPath) noexcept
      -> std::unique_ptr<Shader>;

  /**
   * \name Interface methods.
   *
   * Virtual methods that require implementation.
   * Please refer to concrete implementations for detailed descriptions.
   */
  virtual auto bind() const noexcept -> void = 0;
  virtual auto unbind() const noexcept -> void = 0;

  virtual auto setInt(std::string_view name, int32_t value) const noexcept
      -> void = 0;
  virtual auto setFloat(std::string_view name, float value) const noexcept
      -> void = 0;
  virtual auto setVec2(std::string_view name,
                       const glm::vec2& value) const noexcept -> void = 0;
  virtual auto setVec3(std::string_view name,
                       const glm::vec3& value) const noexcept -> void = 0;
  virtual auto setVec4(std::string_view name,
                       const glm::vec4& value) const noexcept -> void = 0;
  virtual auto setMat4(std::string_view name,
                       const glm::mat4& value) const noexcept -> void = 0;
};
}  // namespace slim

#endif  // SLIM_RENDERER_SHADER_HPP_
