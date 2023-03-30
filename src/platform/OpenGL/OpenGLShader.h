#ifndef SLIM_OPENGLSHADER_H
#define SLIM_OPENGLSHADER_H

#include "rendering/shader.h"
#include <string>
#include <string_view>
#include <glm/glm.hpp>

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

    void setFloat(const std::string& name, float value) override;
    void setFloat2(const std::string& name, const glm::vec2& value) override;
    void setFloat3(const std::string& name, const glm::vec3& value) override;
    void setFloat4(const std::string& name, const glm::vec4& value) override;

    void setMat2(const std::string& name, const glm::mat2& value) override;
    void setMat3(const std::string& name, const glm::mat3& value) override;
    void setMat4(const std::string& name, const glm::mat4& value) override;

    void setInt(const std::string& name, uint32_t value) override;

  private:
    const uint16_t m_logLength = 512;
    uint32_t m_id;

    uint32_t createShader(std::string_view path, OpenGLShaderType shaderType);
  };
}

#endif