#ifndef SLIM_OPENGLSHADER_H
#define SLIM_OPENGLSHADER_H

#include "rendering/shader.h"

#include <string_view>

namespace slim
{
  enum OpenGLShaderType
  {
    Vertex,
    Fragment
  };

  class OpenGLShader : public Shader
  {
  public:
    OpenGLShader(std::string_view vertexPath, std::string_view fragmentPath);
    virtual ~OpenGLShader();

    void bind() override;
    void unbind() override;

  private:
    const uint16_t _LOG_LENGTH = 512;
    uint32_t _id;

    uint32_t createShader(std::string_view path, OpenGLShaderType shaderType);
  };
}

#endif