#ifndef SLIM_SPOTLIGHT_H
#define SLIM_SPOTLIGHT_H

#include "scene/lighting/light.h"
#include "rendering/shader.h"
#include <glm/glm.hpp>
#include <string>

namespace slim
{
  class SpotLight : public Light
  {
  public:
    SpotLight(const glm::vec3& position = {0.0f, 0.0f, 0.0f}, const glm::vec3& direction = {0.0f, 1.0f, 0.0f}, const glm::vec3& color = {1.0f, 1.0f, 1.0f}, float intensity = 1.0f, float range = 5.0f, float angle = 45.0f);
    ~SpotLight() = default;

    void use(const std::unique_ptr<Shader>& shader, const std::string& prefix = "uSpotLight") const override;

    glm::vec3 getPosition() const;
    void setPosition(const glm::vec3& position);

    glm::vec3 getDirection() const;
    void setDirection(const glm::vec3& direction);

    float getRange() const;
    void setRange(float range);

    float getAngle() const;
    void setAngle(float angle);

  private:
    glm::vec3 m_position;
    glm::vec3 m_direction;
    float m_range;
    float m_angle;
  };
}

#endif