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
    m_dirLight = DirectionalLight(m_dirLightColor, m_dirLightIntensity, m_dirLightDirection);
    m_pointLight = PointLight(m_lightPosition, m_lightColor, m_lightIntensity, m_lightRadius);
    m_spotLight = SpotLight(m_spotLightPosition, m_spotLightDirection, m_spotLightColor, m_spotLightIntensity, m_spotLightRange, m_spotLightAngle);
    m_camera = FreeCamera(m_cameraPosition, m_cameraPitch, m_cameraYaw, m_cameraFov);
  }

  void DemoScene::onUpdate()
  {
    m_camera.onUpdate();
    m_cameraPosition = m_camera.getPosition();
    m_cameraPitch = m_camera.getPitch();
    m_cameraYaw = m_camera.getYaw();
    m_cameraFov = m_camera.getFov();

    m_dirLight.setColor(m_dirLightColor);
    m_dirLight.setIntensity(m_dirLightIntensity);
    m_dirLight.setDirection(m_dirLightDirection);

    m_pointLight.setPosition(m_lightPosition);
    m_pointLight.setColor(m_lightColor);
    m_pointLight.setIntensity(m_lightIntensity);
    m_pointLight.setRadius(m_lightRadius);

    m_spotLight.setPosition(m_spotLightPosition);
    m_spotLight.setDirection(m_spotLightDirection);
    m_spotLight.setColor(m_spotLightColor);
    m_spotLight.setIntensity(m_spotLightIntensity);
    m_spotLight.setRange(m_spotLightRange);
    m_spotLight.setAngle(m_spotLightAngle);

    m_cubeShader->bind();
    m_cubeShader->setMat4("uView", m_camera.getView());
    m_cubeShader->setMat4("uProjection", m_camera.getProjection());
    m_cubeShader->setFloat3("uViewPosition", m_camera.getPosition());

    m_dirLight.use(m_cubeShader);
    m_pointLight.use(m_cubeShader);
    m_spotLight.use(m_cubeShader);
    m_material.use(m_cubeShader);

    m_cubeVao->bind();
    for (auto&& position : s_cubePositions)
    {
      glm::mat4 model(1.0f);
      model = glm::translate(model, position);
      m_cubeShader->setMat4("uModel", model);

      glDrawArrays(GL_TRIANGLES, 0, s_indicesCount);
    }

    glm::mat4 lightModel{1.0f};
    lightModel = glm::translate(lightModel, m_lightPosition);
    lightModel = glm::scale(lightModel, {0.25f, 0.25f, 0.25f});

    m_lightShader->bind();
    m_lightShader->setMat4("uModel", lightModel);
    m_lightShader->setMat4("uView", m_camera.getView());
    m_lightShader->setMat4("uProjection", m_camera.getProjection());
    m_lightShader->setFloat3("uColor", m_pointLight.getColor());

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

    ImGui::SeparatorText("Camera");
    if (ImGui::SliderFloat3("Position", glm::value_ptr(m_cameraPosition), -10.0f, 10.0f))
      m_camera.setPosition(m_cameraPosition);

    if (ImGui::SliderFloat("Pitch", &m_cameraPitch, -79.0f, 79.0f))
      m_camera.setPitch(m_cameraPitch);

    if (ImGui::SliderFloat("Yaw", &m_cameraYaw, -179.0f, 179.0f))
      m_camera.setYaw(m_cameraYaw);

    if (ImGui::SliderFloat("FOV", &m_cameraFov, 20.0f, 90.0f))
      m_camera.setFov(m_cameraFov);

    ImGui::SeparatorText("Material");
    ImGui::SliderFloat3("Material Ambient", glm::value_ptr(m_material.ambient), 0.0f, 1.0f);
    ImGui::SliderFloat3("Material Diffuse", glm::value_ptr(m_material.diffuse), 0.0f, 1.0f);
    ImGui::SliderFloat3("Material Specular", glm::value_ptr(m_material.specular), 0.0f, 1.0f);
    ImGui::SliderFloat("Material Shininess", &m_material.shininess, 2, 512);

    ImGui::SeparatorText("Directional Light");
    ImGui::ColorEdit3("Dir. Light Color", glm::value_ptr(m_dirLightColor));
    ImGui::SliderFloat("Dir. Light Intensity", &m_dirLightIntensity, 0.0f, 1.0f);
    ImGui::SliderFloat3("Dir. Light Direction", glm::value_ptr(m_dirLightDirection), -1.0f, 1.0f);

    ImGui::SeparatorText("Point Light");
    ImGui::SliderFloat3("Point Light Position", glm::value_ptr(m_lightPosition), -25.0f, 25.0f);
    ImGui::ColorEdit3("Point Light Color", glm::value_ptr(m_lightColor));
    ImGui::SliderFloat("Point Light Intensity", &m_lightIntensity, 0.0f, 1.0f);
    ImGui::SliderFloat("Point Light Radius", &m_lightRadius, 0.1f, 20.0f);

    ImGui::SeparatorText("Spot Light");
    ImGui::SliderFloat3("Spot Light Position", glm::value_ptr(m_spotLightPosition), -25.0f, 25.0f);
    ImGui::SliderFloat3("Spot Light Direction", glm::value_ptr(m_spotLightDirection), -1.0f, 1.0f);
    ImGui::ColorEdit3("Spot Light Color", glm::value_ptr(m_spotLightColor));
    ImGui::SliderFloat("Spot Light Intensity", &m_spotLightIntensity, 0.0f, 1.0f);
    ImGui::SliderFloat("Spot Light Range", &m_spotLightRange, 0.1f, 50.0f);
    ImGui::SliderFloat("Spot Light Angle", &m_spotLightAngle, 0.1f, 89.0f);

    ImGui::End();

    ImGui::ShowMetricsWindow();
  }

  void DemoScene::onDetach()
  {
    m_cubeVao->~VertexArray();
    m_lightVao->~VertexArray();
  }
}