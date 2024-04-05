#include "slim/renderer/shader.hpp"

// IWYU pragma: no_include <__exception/terminate.h>

#include <exception>  // IWYU pragma: keep
#include <memory>
#include <string_view>

#include "slim/core/error.hpp"
#include "slim/platform/opengl/opengl_shader.hpp"
#include "slim/renderer/renderer.hpp"

namespace slim {
auto Shader::create(std::string_view vertexShaderPath,
                    std::string_view fragmentShaderPath) noexcept
    -> std::unique_ptr<Shader> {
  switch (Renderer::getAPI()) {
    [[likely]] case Renderer::API::OpenGL:
      return std::make_unique<OpenGLShader>(vertexShaderPath,
                                            fragmentShaderPath);
    [[unlikely]] default:
      SLIM_CORE_FATAL_ERROR("Invalid Renderer::API");
  }
}
}  // namespace slim
