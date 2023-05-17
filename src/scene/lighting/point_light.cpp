#include "scene/lighting/point_light.h"
#include "point_light.h"

namespace slim
{
  PointLight::PointLight(const glm::vec3 &position, const glm::vec3 &color, float intensity, float radius)
  {
    m_position = position;
    m_color = color;
  }

  void PointLight::use(const std::unique_ptr<Shader>& shader, const std::string& prefix = "uPointLight") const
  {
    shader->setFloat3(prefix + ".position", m_position);
    shader->setFloat3(prefix + ".color", m_position);
    shader->setFloat(prefix + ".intensity", m_intensity);
    shader->setFloat(prefix + ".radius", m_radius);
  }

  glm::vec3 PointLight::getPosition() const
  {
    return m_position;
  }

  void PointLight::setPosition(const glm::vec3 &position)
  {
    m_position = position;
  }

  glm::vec3 PointLight::getColor() const
  {
    return m_color;
  }

  void PointLight::setColor(const glm::vec3& color)
  {
    m_color = color;
  }

  float PointLight::getIntensity() const
  {
    return m_intensity;
  }

  void PointLight::setIntensity(float intensity)
  {
    SLIM_DEBUG_ASSERT(intensity >= 0.0f, "Intensity must be >= 0.0f, but is {}", intensity)
    m_intensity = intensity;
  }

  float PointLight::getRadius() const
  {
    return m_radius;
  }

  void PointLight::setRadius(float radius)
  {
    SLIM_DEBUG_ASSERT(radius > 0.0f, "Radius must be > 0.0f, but is {}", radius)
    m_radius = radius;
  }
}