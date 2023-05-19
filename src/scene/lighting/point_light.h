#ifndef SLIM_POINTLIGHT_H
#define SLIM_POINTLIGHT_H

#include "scene/lighting/light.h"
#include "core/base.h"
#include <glm/glm.hpp>

namespace slim
{
  class PointLight : public Light
  {
  public:
    PointLight(const glm::vec3& position = {0.0f, 0.0f, 0.0f}, const glm::vec3& color = {1.0f, 1.0f, 1.0f}, float intensity = 1.0f, float radius = 10.0f);
    ~PointLight() = default;

    void use(const std::unique_ptr<Shader>& shader, const std::string& prefix = "uPointLight") const override;

    glm::vec3 getColor() const override;
    void setColor(const glm::vec3& color) override;

    float getIntensity() const override;
    void setIntensity(float intensity) override;

    glm::vec3 getPosition() const;
    void setPosition(const glm::vec3& position);

    float getRadius() const;
    void setRadius(float radius);

  private:
    glm::vec3 m_color;
    float m_intensity;
    glm::vec3 m_position;
    float m_radius;
  };
}

#endif