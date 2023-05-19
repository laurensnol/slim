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

    virtual glm::vec3 getColor() const { return m_color; }
    virtual void setColor(const glm::vec3& color) { m_color = color; }

    virtual float getIntensity() const { return m_intensity; }
    virtual void setIntensity(float intensity)
    {
      SLIM_DEBUG_ASSERT(intensity >= 0.0f, "Intensity must be >= 0.0f, but is {}", intensity)
      m_intensity = intensity;
    }

  protected:
    glm::vec3 m_color;
    float m_intensity;
  };
}

#endif