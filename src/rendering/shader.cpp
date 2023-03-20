#include "rendering/shader.h"

#include "rendering/renderer.h"
#include "platform/OpenGL/OpenGLShader.h"
#include <spdlog/spdlog.h>

namespace slim
{
  std::unique_ptr<Shader> Shader::create(std::string_view vertexPath, std::string_view fragmentPath)
  {
    if (Renderer::api() == RendererApi::OpenGL)
    {
      return std::make_unique<OpenGLShader>(vertexPath, fragmentPath);
    }
    else
    {
      spdlog::critical("API not implemented");
      assert(false);
    }
  }
}