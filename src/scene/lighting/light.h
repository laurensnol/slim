#ifndef SLIM_LIGHT_H
#define SLIM_LIGHT_H

#include "core/base.h"
#include "rendering/shader.h"
#include <glm/glm.hpp>
#include <string>

namespace slim
{
  class Light
  {
  public:
    virtual ~Light() = default;

    virtual void use(const std::unique_ptr<Shader>& shader, const std::string& prefix) const = 0;

    virtual glm::vec3 getColor() const = 0;
    virtual void setColor(const glm::vec3& color) = 0;

    virtual float getIntensity() const = 0;
    virtual void setIntensity(float intensity) = 0;
  };
}

#endif