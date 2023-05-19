#ifndef SLIM_DIRECTIONALLIGHT_H
#define SLIM_DIRECTIONALLIGHT_H

#include "scene/lighting/light.h"
#include <glm/glm.hpp>

namespace slim
{
  class DirectionalLight : public Light
  {
  public:
    DirectionalLight(const glm::vec3& color = {1.0f, 1.0f, 1.0f}, float intensity = 1.0f, const glm::vec3& direction = {0.0f, 0.0f, 0.0f});
    ~DirectionalLight() = default;

    void use(const std::unique_ptr<Shader>& shader, const std::string& prefix = "uDirectionalLight") const override;

    glm::vec3 getDirection() const;
    void setDirection(const glm::vec3& direction);

  private:
    glm::vec3 m_direction;
  };
}

#endif