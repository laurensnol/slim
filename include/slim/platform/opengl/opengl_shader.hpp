#ifndef SLIM_PLATFORM_OPENGL_SHADER_HPP_
#define SLIM_PLATFORM_OPENGL_SHADER_HPP_

// IWYU pragma: no_include <__fwd/string_view.h>

#include <glad/gl.h>

#include <cstdint>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <string_view>  // IWYU pragma: keep

#include "slim/renderer/shader.hpp"

namespace slim {
/**
 * \brief Implements \ref Shader for the OpenGL graphics API.
 */
class OpenGLShader : public Shader {
public:
  OpenGLShader(std::string_view vertexShaderPath,
               std::string_view fragmentShaderPath) noexcept;
  OpenGLShader(const OpenGLShader&) = delete;
  OpenGLShader(OpenGLShader&&) = delete;
  auto operator=(const OpenGLShader&) -> OpenGLShader& = delete;
  auto operator=(OpenGLShader&&) -> OpenGLShader& = delete;
  ~OpenGLShader() noexcept override;

  auto bind() const noexcept -> void override;
  auto unbind() const noexcept -> void override;

  auto setInt(std::string_view name, int32_t value) const noexcept
      -> void override;
  auto setFloat(std::string_view name, float value) const noexcept
      -> void override;
  auto setVec2(std::string_view name, const glm::vec2& value) const noexcept
      -> void override;
  auto setVec3(std::string_view name, const glm::vec3& value) const noexcept
      -> void override;
  auto setVec4(std::string_view name, const glm::vec4& value) const noexcept
      -> void override;
  auto setMat4(std::string_view name, const glm::mat4& value) const noexcept
      -> void override;

private:
  GLuint program_ = 0;
};
}  // namespace slim

#endif  // SLIM_PLATFORM_OPENGL_SHADER_HPP_
