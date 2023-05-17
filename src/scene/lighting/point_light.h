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

    glm::vec3 getPosition() const override;
    void setPosition(const glm::vec3& position) override;

    glm::vec3 getColor() const override;
    void setColor(const glm::vec3& color) override;

    float getIntensity() const override;
    void setIntensity(float intensity) override;

    float getRadius() const;
    void setRadius(float radius);

  private:
    float m_radius;
  };
}