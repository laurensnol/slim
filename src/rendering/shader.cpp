#include "rendering/shader.h"

#include "rendering/renderer.h"
#include "platform/OpenGL/OpenGLShader.h"
#include "core/base.h"

namespace slim
{
  std::unique_ptr<Shader> Shader::create(std::string_view vertexPath, std::string_view fragmentPath)
  {
    if (Renderer::api() == RendererApi::OpenGL)
      return std::make_unique<OpenGLShader>(vertexPath, fragmentPath);
    else
      SLIM_ASSERT(false, "API not implemented")
  }
}