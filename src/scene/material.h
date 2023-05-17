#ifndef SLIM_MATERIAL_H
#define SLIM_MATERIAL_H

#include "rendering/shader.h"
#include <string>
#include <glm/glm.hpp>

namespace slim
{
  struct Material
  {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;

    void use(const std::unique_ptr<Shader>& shader, const std::string& prefix = "uMaterial") const
    {
      shader->setFloat3(prefix + ".ambient", ambient);
      shader->setFloat3(prefix + ".diffuse", diffuse);
      shader->setFloat3(prefix + ".specular", specular);
      shader->setFloat(prefix + ".shininess", shininess);
    }
  };
}

#endif
