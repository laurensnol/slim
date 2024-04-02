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
class Shader {  // NOLINT(cppcoreguidelines-special-member-functions)
public:
  virtual ~Shader() noexcept = default;

  static auto create(std::string_view vertexShaderPath,
                     std::string_view fragmentShaderPath) noexcept
      -> std::unique_ptr<Shader>;

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
