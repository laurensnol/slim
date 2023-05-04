#include "demo_scene.h"
#include "core/application.h"
#include <glm/gtc/type_ptr.hpp>
#include <glad/gl.h>
#include <imgui.h>

namespace slim
{
  float DemoScene::s_vertices[] = {
    -1.0, -1.0, -1.0, // Back Bottom Left
     1.0, -1.0, -1.0, // Back Bottom Right
     1.0,  1.0, -1.0, // Back Top Right
    -1.0,  1.0, -1.0, // Back Top Left
    -1.0, -1.0,  1.0, // Front Bottom Left
     1.0, -1.0,  1.0, // Front Bottom Right
     1.0,  1.0,  1.0, // Front Top Right
    -1.0,  1.0,  1.0  // Front Top Left
  };

  uint32_t DemoScene::s_indices[] = {
    0, 1, 3, 3, 1, 2,
    1, 5, 2, 2, 5, 6,
    5, 4, 6, 6, 4, 7,
    4, 0, 7, 7, 0, 3,
    3, 2, 7, 7, 2, 6,
    4, 5, 0, 0, 5, 1
  };

  const glm::vec3 DemoScene::s_cubePositions[s_cubeCount] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 0.0f,  0.0f,  2.0f),
    glm::vec3( 2.0f,  5.0f, -9.0f),
    glm::vec3(-1.5f, -2.5f,  2.5f),
    glm::vec3(-3.5f, -2.0f,  7.0f),
    glm::vec3( 1.5f,  4.0f, -1.5f)
  };

  void DemoScene::onAttach()
  {
    std::shared_ptr<slim::VertexBuffer> vbo = VertexBuffer::create(s_vertices, sizeof(s_vertices));

    VertexAttribute vertexAttribute = VertexAttribute(0, VertexAttributeBaseType::Float3, false, 3);
    vbo->addAttribute(vertexAttribute);

    m_vao = VertexArray::create();
    m_vao->addVertexBuffer(vbo);

    std::shared_ptr<IndexBuffer> ibo = IndexBuffer::create(s_indices, s_indicesCount);
    m_vao->setIndexBuffer(ibo);
    
    m_shader = Shader::create("res/flat.vert", "res/flat.frag");
    m_shader->setFloat4("uColor", {1.0f, 0.0f, 0.0f, 1.0f});
    m_shader->setFloat4("uLightColor", {1.0f, 1.0f, 1.0f, 1.0f});
    m_shader->setMat4("uView", m_camera.getView());
    m_shader->setMat4("uProjection", m_camera.getProjection());

    m_camera = FreeCamera(m_cameraPosition, m_cameraPitch, m_cameraYaw, m_cameraFov);
  }

  void DemoScene::onUpdate()
  {
    m_camera.onUpdate();

    m_shader->setMat4("uView", m_camera.getView());
    m_shader->setMat4("uProjection", m_camera.getProjection());
    m_vao->bind();

    m_cameraPosition = m_camera.getPosition();
    m_cameraPitch = m_camera.getPitch();
    m_cameraYaw = m_camera.getYaw();
    m_cameraFov = m_camera.getFov();

    for (int i = 0; i < s_cubeCount; i++)
    {
      glm::mat4 model(1.0f);
      model = glm::translate(model, s_cubePositions[i]);
      m_shader->setMat4("uModel", model);

      glDrawElements(GL_TRIANGLES, s_indicesCount, GL_UNSIGNED_INT, 0);
    }
  }

  void DemoScene::onUiDraw()
  {
    ImGui::Begin("Settings");

    if (ImGui::Checkbox("VSync", &m_vsync))
      Application::getInstance().getWindow().setVsync(m_vsync);

    if (ImGui::Checkbox("Wireframes", &m_wireframes))
      glPolygonMode(GL_FRONT_AND_BACK, m_wireframes ? GL_LINE : GL_FILL);

    ImGui::Text("Camera");
    if (ImGui::SliderFloat3("Position", glm::value_ptr(m_cameraPosition), -10.0f, 10.0f))
      m_camera.setPosition(m_cameraPosition);

    if (ImGui::SliderFloat("Pitch", &m_cameraPitch, -79.0f, 79.0f))
      m_camera.setPitch(m_cameraPitch);

    if (ImGui::SliderFloat("Yaw", &m_cameraYaw, -179.0f, 179.0f))
      m_camera.setYaw(m_cameraYaw);

    if (ImGui::SliderFloat("FOV", &m_cameraFov, 20.0f, 90.0f))
      m_camera.setFov(m_cameraFov);

    ImGui::End();

    ImGui::ShowMetricsWindow();
  }

  void DemoScene::onDetach()
  {
    m_vao->~VertexArray();
  }
}