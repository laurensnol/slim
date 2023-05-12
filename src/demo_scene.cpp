#include "demo_scene.h"
#include "core/application.h"
#include <glm/gtc/type_ptr.hpp>
#include <glad/gl.h>
#include <imgui.h>

namespace slim
{
  float DemoScene::s_vertices[] = {
    // Position           Normals
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
  };

  const glm::vec3 DemoScene::s_cubePositions[s_cubeCount] = {
    glm::vec3( 4.0f,  0.0f,  0.0f),
    glm::vec3( 0.0f,  0.0f,  4.0f),
    glm::vec3(-1.0f,  2.0f, -3.0f),
    glm::vec3(-1.5f, -2.5f,  2.5f),
    glm::vec3(-3.5f, -2.0f,  7.0f),
    glm::vec3( 1.5f,  4.0f, -1.5f)
  };

  void DemoScene::onAttach()
  {
    std::shared_ptr<VertexBuffer> vbo = VertexBuffer::create(s_vertices, sizeof(s_vertices));

    VertexAttribute positionAttribute{0, VertexAttributeBaseType::Float3, false, 6};
    vbo->addAttribute(positionAttribute);

    VertexAttribute normalAttribute{1, VertexAttributeBaseType::Float3, false, 6, 3};
    vbo->addAttribute(normalAttribute);

    m_cubeVao = VertexArray::create();
    m_cubeVao->addVertexBuffer(vbo);

    m_lightVao = VertexArray::create();
    m_lightVao->addVertexBuffer(vbo);
    
    m_cubeShader = Shader::create("res/flat.vert", "res/flat.frag");
    m_lightShader = Shader::create("res/light.vert", "res/light.frag");

    glm::mat4 lightModel{1.0f};
    lightModel = glm::translate(lightModel, m_light.position);
    lightModel = glm::scale(lightModel, {0.25f, 0.25f, 0.25f});
    m_lightShader->setMat4("uModel", lightModel);

    m_camera = FreeCamera(m_cameraPosition, m_cameraPitch, m_cameraYaw, m_cameraFov);
  }

  void DemoScene::onUpdate()
  {
    m_camera.onUpdate();
    m_cameraPosition = m_camera.getPosition();
    m_cameraPitch = m_camera.getPitch();
    m_cameraYaw = m_camera.getYaw();
    m_cameraFov = m_camera.getFov();

    m_cubeShader->bind();
    m_cubeShader->setMat4("uView", m_camera.getView());
    m_cubeShader->setMat4("uProjection", m_camera.getProjection());
    m_cubeShader->setFloat3("uViewPosition", m_camera.getPosition());
    m_cubeShader->setFloat3("uLight.position", m_light.position);
    m_cubeShader->setFloat3("uLight.ambient", m_light.ambient);
    m_cubeShader->setFloat3("uLight.diffuse", m_light.diffuse);
    m_cubeShader->setFloat3("uLight.specular", m_light.specular);
    m_cubeShader->setFloat3("uMaterial.ambient", m_material.ambient);
    m_cubeShader->setFloat3("uMaterial.diffuse", m_material.diffuse);
    m_cubeShader->setFloat3("uMaterial.specular", m_material.specular);
    m_cubeShader->setFloat("uMaterial.shininess", m_material.shininess);
    m_cubeVao->bind();

    for (auto&& position : s_cubePositions)
    {
      glm::mat4 model(1.0f);
      model = glm::translate(model, position);
      m_cubeShader->setMat4("uModel", model);

      glDrawArrays(GL_TRIANGLES, 0, s_indicesCount);
    }

    m_lightShader->bind();
    m_lightShader->setMat4("uView", m_camera.getView());
    m_lightShader->setMat4("uProjection", m_camera.getProjection());
    m_lightShader->setFloat3("uColor", {1.0f, 1.0f, 1.0f});
    m_lightVao->bind();

    glDrawArrays(GL_TRIANGLES, 0, s_indicesCount);
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

    ImGui::Text("Light");
    if (ImGui::SliderFloat3("Light Position", glm::value_ptr(m_light.position), -10.0f, 10.0f))
    {
      glm::mat4 lightModel{1.0f};
      lightModel = glm::translate(lightModel, m_light.position);
      lightModel = glm::scale(lightModel, {0.25f, 0.25f, 0.25f});
      m_lightShader->setMat4("uModel", lightModel);
    }

    ImGui::SliderFloat3("Light Ambient", glm::value_ptr(m_light.ambient), -1.0f, 1.0f);
    ImGui::SliderFloat3("Light Specular", glm::value_ptr(m_light.diffuse), -1.0f, 1.0f);
    ImGui::SliderFloat3("Light Diffuse", glm::value_ptr(m_light.specular), -1.0f, 1.0f);

    ImGui::Text("Material");
    ImGui::SliderFloat3("Material Ambient", glm::value_ptr(m_material.ambient), 0.0f, 1.0f);
    ImGui::SliderFloat3("Material Diffuse", glm::value_ptr(m_material.diffuse), 0.0f, 1.0f);
    ImGui::SliderFloat3("Material Specular", glm::value_ptr(m_material.specular), 0.0f, 1.0f);
    ImGui::SliderFloat("Material Shininess", &m_material.shininess, 2, 512);

    ImGui::End();

    ImGui::ShowMetricsWindow();
  }

  void DemoScene::onDetach()
  {
    m_cubeVao->~VertexArray();
    m_lightVao->~VertexArray();
  }
}