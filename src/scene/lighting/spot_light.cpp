#include "scene/lighting/spot_light.h"
#include "core/base.h"
#include "spot_light.h"

namespace slim
{
  SpotLight::SpotLight(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& color, float intensity, float range, float angle)
  {
    m_position = position;
    m_color = color;
    m_direction = direction;
    setIntensity(intensity);
    setRange(range);
    setAngle(angle);
  }

  void SpotLight::use(const std::unique_ptr<Shader>& shader, const std::string& prefix) const
  {
    shader->setFloat3(prefix + ".position", m_position);
    shader->setFloat3(prefix + ".color", m_color);
    shader->setFloat3(prefix + ".direction", m_direction);
    shader->setFloat(prefix + ".intensity", m_intensity);
    shader->setFloat(prefix + ".range", m_range);
    shader->setFloat(prefix + ".angle", m_angle);
  }

  glm::vec3 SpotLight::getPosition() const
  {
    return m_position;
  }

  void SpotLight::setPosition(const glm::vec3& position)
  {
    m_position = position;
  }

  glm::vec3 SpotLight::getDirection() const
  {
    return m_direction;
  }

  void SpotLight::setDirection(const glm::vec3& direction)
  {
    m_direction = direction;
  }

  float SpotLight::getRange() const
  {
    return m_range;
  }

  void SpotLight::setRange(float range)
  {
    SLIM_DEBUG_ASSERT(range > 0.0f, "Range must be > 0.0f, but is {}", range);
    m_range = range;
  }

  float SpotLight::getAngle() const
  {
    return m_angle;
  }

  void SpotLight::setAngle(float angle)
  {
    SLIM_DEBUG_ASSERT(angle > 0.0f, "Angle must be > 0.0f, but is {}", angle);
    m_angle = angle;
  }
}