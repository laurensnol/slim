#ifndef SLIM_PLATFORM_SHADER_H
#define SLIM_PLATFORM_SHADER_H

#include <string>
#include <string_view>
#include <glm/glm.hpp>
#include <memory>

namespace slim
{
  class Shader
  {
  public:
    virtual ~Shader() = default;

    virtual void bind() = 0;
    virtual void unbind() = 0;

    virtual void setFloat(const std::string &name, float value) = 0;
    virtual void setFloat2(const std::string &name, const glm::vec2 &value) = 0;
    virtual void setFloat3(const std::string &name, const glm::vec3 &value) = 0;
    virtual void setFloat4(const std::string &name, const glm::vec4 &value) = 0;

    virtual void setMat2(const std::string &name, const glm::mat2 &value) = 0;
    virtual void setMat3(const std::string &name, const glm::mat3 &value) = 0;
    virtual void setMat4(const std::string &name, const glm::mat4 &value) = 0;

    virtual void setInt(const std::string &name, uint32_t value) = 0;

    static std::unique_ptr<Shader> create(std::string_view vertexPath, std::string_view fragmentPath);
  };
}

#endif