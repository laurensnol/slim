#include "rendering/shader.h"

#include "platform/OpenGL/OpenGLShader.h"

namespace slim
{
  std::unique_ptr<Shader> Shader::create(std::string_view vertexPath, std::string_view fragmentPath)
  {
    // TODO: Implement

    /*#ifdef SLIM_API_OPENGL
      return std::make_unique<OpenGLShader>(vertexPath, fragmentPath);
    #else
      spdlog::critical("API not implemented");
      assert(false);
    #endif*/

    return std::make_unique<OpenGLShader>(vertexPath, fragmentPath);
  }
}