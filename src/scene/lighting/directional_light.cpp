#include "scene/lighting/directional_light.h"
#include "core/base.h"

namespace slim
{
  DirectionalLight::DirectionalLight(const glm::vec3& color, float intensity, const glm::vec3& direction)
  {
    m_color = color;
    m_direction = direction;
    setIntensity(intensity);
  }

  void DirectionalLight::use(const std::unique_ptr<Shader>& shader, const std::string& prefix) const
  {
    shader->setFloat3(prefix + ".color", m_color);
    shader->setFloat(prefix + ".intensity", m_intensity);
    shader->setFloat3(prefix + ".direction", m_direction);
  }

  glm::vec3 DirectionalLight::getDirection() const
  {
    return m_direction;
  }

  void DirectionalLight::setDirection(const glm::vec3& direction)
  {
    m_direction = direction;
  }
}