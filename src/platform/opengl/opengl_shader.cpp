#include "slim/platform/opengl/opengl_shader.hpp"

// IWYU pragma: no_include <glm/detail/qualifier.hpp>
// IWYU pragma: no_include <glm/detail/type_mat4x4.inl>

#include <glad/gl.h>

#include <cstdint>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glm/gtc/type_ptr.inl>
#include <string>
#include <string_view>

#include "slim/core/assert.hpp"
#include "slim/core/filesystem.hpp"

namespace slim {
OpenGLShader::OpenGLShader(std::string_view vertexShaderPath,
                           std::string_view fragmentShaderPath) noexcept {
  const std::string vertexShaderSource =
      Filesystem::strFromFile(vertexShaderPath);
  const auto* vertexShaderSourceStr = vertexShaderSource.c_str();

  const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSourceStr, nullptr);
  glCompileShader(vertexShader);

  // TODO(laurensnol): Error handling

  const std::string fragmentShaderSource =
      Filesystem::strFromFile(fragmentShaderPath);
  const auto* fragmentShaderSourceStr = fragmentShaderSource.c_str();

  const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSourceStr, nullptr);
  glCompileShader(fragmentShader);

  program_ = glCreateProgram();  // NOLINT
  SLIM_CORE_ASSERT(program_ != 0, "Failed to create program");

  glAttachShader(program_, vertexShader);
  glAttachShader(program_, fragmentShader);
  glLinkProgram(program_);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

OpenGLShader::~OpenGLShader() noexcept { glDeleteProgram(program_); }

auto OpenGLShader::bind() const noexcept -> void { glUseProgram(program_); }

auto OpenGLShader::unbind() const noexcept -> void { glUseProgram(0); }

auto OpenGLShader::setInt(std::string_view name, int32_t value) const noexcept
    -> void {
  auto location = glGetUniformLocation(program_, name.data());
  glUniform1i(location, value);
}

auto OpenGLShader::setFloat(std::string_view name, float value) const noexcept
    -> void {
  auto location = glGetUniformLocation(program_, name.data());
  glUniform1f(location, value);
}

auto OpenGLShader::setVec2(std::string_view name,
                           const glm::vec2& value) const noexcept -> void {
  auto location = glGetUniformLocation(program_, name.data());
  glUniform2f(location, value.x, value.y);
}

auto OpenGLShader::setVec3(std::string_view name,
                           const glm::vec3& value) const noexcept -> void {
  auto location = glGetUniformLocation(program_, name.data());
  glUniform3f(location, value.x, value.y, value.z);
}

auto OpenGLShader::setVec4(std::string_view name,
                           const glm::vec4& value) const noexcept -> void {
  auto location = glGetUniformLocation(program_, name.data());
  glUniform4f(location, value.x, value.y, value.z, value.w);
}

auto OpenGLShader::setMat4(std::string_view name,
                           const glm::mat4& value) const noexcept -> void {
  auto location = glGetUniformLocation(program_, name.data());
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
}  // namespace slim
