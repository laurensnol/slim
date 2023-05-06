#ifndef SLIM_DEMOSCENE_H
#define SLIM_DEMOSCENE_H

#include "scene/scene.h"
#include "rendering/vertex_buffer.h"
#include "rendering/vertex_attribute.h"
#include "rendering/vertex_array.h"
#include "rendering/shader.h"
#include "rendering/free_camera.h"
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
    static uint32_t s_indices[];
    static const glm::vec3 s_cubePositions[s_cubeCount];

    std::shared_ptr<VertexArray> m_cubeVao;
    std::shared_ptr<VertexArray> m_lightVao;
    std::unique_ptr<Shader> m_cubeShader;
    std::unique_ptr<Shader> m_lightShader;
    FreeCamera m_camera;

    glm::vec3 m_lightPosition{0.0f, 0.0f, 0.0f};
    glm::vec3 m_cameraPosition{-10.0f, 3.0f, 0.0f};
    float m_cameraPitch = -15;
    float m_cameraYaw = 0;
    float m_cameraFov = 60.0f;
    bool m_vsync = false;
    bool m_wireframes = false;
  };
}

#endif