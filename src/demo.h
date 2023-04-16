#ifndef SLIM_DEMO_H
#define SLIM_DEMO_H

#include "rendering/vertex_buffer.h"
#include "rendering/vertex_attribute.h"
#include "rendering/vertex_array.h"
#include "rendering/shader.h"
#include "rendering/cubemap.h"
#include "rendering/free_camera.h"
#include <glm/glm.hpp>
#include <memory>

namespace slim
{
  class Demo
  {
  public:
    Demo();

    void update();

  private:
    static const uint32_t s_cubeCount = 6;
    static const uint32_t s_indicesCount = 36;
    static float s_vertices[];
    static uint32_t s_indices[];
    static const glm::vec3 s_cubePositions[s_cubeCount];

    VertexAttribute m_vertexAttribute = VertexAttribute(0, VertexAttributeBaseType::Float3, false, 6);
    VertexAttribute m_colorAttribute = VertexAttribute(1, VertexAttributeBaseType::Float3, false, 6, 3 * sizeof(float));
    std::shared_ptr<VertexArray> m_vao;
    std::shared_ptr<Cubemap> m_cubemap;
    std::unique_ptr<Shader> m_shader;
    FreeCamera m_camera;

    float m_cameraPosition[3] = {-10, 3, 0};
    float m_cameraPitch = -15;
    float m_cameraYaw = 0;
    float m_cameraFov = 60.0f;
    bool m_vsync = false;
    bool m_wireframes = false;
  };
}

#endif