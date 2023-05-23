#ifndef SLIM_DEMOSCENE_H
#define SLIM_DEMOSCENE_H

#include "scene/scene.h"
#include "rendering/vertex_buffer.h"
#include "rendering/vertex_attribute.h"
#include "rendering/vertex_array.h"
#include "rendering/shader.h"
#include "rendering/free_camera.h"
#include "scene/material.h"
#include "scene/lighting/directional_light.h"
#include "scene/lighting/point_light.h"
#include "scene/lighting/spot_light.h"
#include <glm/glm.hpp>
#include <memory>

namespace slim
{
  class DemoScene : public Scene
  {
  public:
    void onAttach() override;
    void onUpdate() override;
    void onUiDraw() override;
    void onDetach() override;

  private:
    static const uint32_t s_cubeCount = 6;
    static const uint32_t s_indicesCount = 36;
    static float s_vertices[];
    static const glm::vec3 s_cubePositions[s_cubeCount];

    std::shared_ptr<VertexArray> m_cubeVao;
    std::shared_ptr<VertexArray> m_lightVao;
    std::unique_ptr<Shader> m_cubeShader;
    std::unique_ptr<Shader> m_lightShader;

    // From: http://devernay.free.fr/cours/opengl/materials.html
    Material m_material{
      {0.0215f, 0.1745f, 0.0215f},
      {0.07568f, 0.61424f, 0.07568f},
      {0.633f, 0.727811f, 0.633f},
      76.8f
    };

    FreeCamera m_camera;
    DirectionalLight m_dirLight;
    PointLight m_pointLight;
    SpotLight m_spotLight;

    // Int. vars
    glm::vec3 m_cameraPosition{-10.0f, 3.0f, 0.0f};
    float m_cameraPitch = -15;
    float m_cameraYaw = 0;
    float m_cameraFov = 60.0f;
    bool m_vsync = true;
    bool m_wireframes = false;

    glm::vec3 m_dirLightColor{1.0f};
    float m_dirLightIntensity = 1.0f;
    glm::vec3 m_dirLightDirection{-0.2f, -1.0f, -0.3f};

    glm::vec3 m_lightPosition{0.0f};
    glm::vec3 m_lightColor{1.0f};
    float m_lightIntensity = 1.0f;
    float m_lightRadius = 10.0f;
  };
}

#endif