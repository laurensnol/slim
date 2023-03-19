#ifndef SLIM_PLATFORM_SHADER_H
#define SLIM_PLATFORM_SHADER_H

#include <memory>
#include <string_view>

namespace slim
{
  class Shader
  {
  public:
    virtual ~Shader() = default;

    virtual void bind() = 0;
    virtual void unbind() = 0;

    static std::unique_ptr<Shader> create(std::string_view vertexPath, std::string_view fragmentPath);
  };
}

#endif