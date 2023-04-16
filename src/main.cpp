#include "core/application.h"

int main()
{  
  slim::Application& app = slim::Application::getInstance();
  app.start();

  return 0;
}

/*
 * Will be moved to their respective classes soon.
 * Keeping it for reference.
 */

/*#include "core/window.h"
#include "core/time.h"
#include "rendering/shader.h"
#include "rendering/vertex_buffer.h"
#include "rendering/vertex_attribute.h"
#include "rendering/vertex_array.h"
#include "rendering/index_buffer.h"
#include "rendering/texture2d.h"
#include "rendering/cubemap.h"
#include "rendering/free_camera.h"
#include "events/event_bus.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/gl.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <stb_image.h>
#include <memory>

int main()
{
  slim::EventBus::init();
  
  std::unique_ptr<slim::Window> window = slim::Window::create();

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGui::StyleColorsDark();

  ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)window->getNative(), true);
  ImGui_ImplOpenGL3_Init("#version 410");

  const int32_t cubeCount = 6;
  glm::vec3 cubePositions[cubeCount] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 0.0f,  0.0f,  2.0f),
    glm::vec3( 2.0f,  5.0f, -9.0f),
    glm::vec3(-1.5f, -2.5f,  2.5f),
    glm::vec3(-3.5f, -2.0f,  7.0f),
    glm::vec3( 1.5f,  4.0f, -1.5f)
  };

  float vertices[] = {
    -1.0, -1.0, -1.0,    0.0, 0.0, 0.0, // Back Bottom Left
     1.0, -1.0, -1.0,    0.0, 1.0, 0.0, // Back Bottom Right
     1.0,  1.0, -1.0,    0.0, 1.0, 1.0, // Back Top Right
    -1.0,  1.0, -1.0,    0.0, 0.0, 1.0, // Back Top Left
    -1.0, -1.0,  1.0,    1.0, 0.0, 0.0, // Front Bottom Left
     1.0, -1.0,  1.0,    1.0, 1.0, 0.0, // Front Bottom Right
     1.0,  1.0,  1.0,    1.0, 1.0, 1.0, // Front Top Right
    -1.0,  1.0,  1.0,    1.0, 0.0, 1.0, // Front Top Left
  };

  uint32_t indexCount = 36;
  uint32_t indices[] = {
    0, 1, 3, 3, 1, 2,
    1, 5, 2, 2, 5, 6,
    5, 4, 6, 6, 4, 7,
    4, 0, 7, 7, 0, 3,
    3, 2, 7, 7, 2, 6,
    4, 5, 0, 0, 5, 1
  };

  std::shared_ptr<slim::VertexBuffer> vbo = slim::VertexBuffer::create(vertices, sizeof(vertices));
  
  slim::VertexAttribute vertexAttr = slim::VertexAttribute(0, slim::VertexAttributeBaseType::Float3, false, 6);
  vbo->addAttribute(vertexAttr);

  slim::VertexAttribute colorAttr = slim::VertexAttribute(1, slim::VertexAttributeBaseType::Float3, false, 6, 3 * sizeof(float));
  vbo->addAttribute(colorAttr);

  std::shared_ptr<slim::VertexArray> vao = slim::VertexArray::create();
  vao->addVertexBuffer(vbo);

  std::shared_ptr<slim::IndexBuffer> ibo = slim::IndexBuffer::create(indices, indexCount);
  vao->setIndexBuffer(ibo);

  std::shared_ptr<slim::Cubemap> cubemap = slim::Cubemap::create("res/cubemap/side.png", "res/cubemap/side.png", "res/cubemap/top.png", "res/cubemap/bottom.png", "res/cubemap/side.png", "res/cubemap/side.png");

  float camPos[] = {-10, 3, 0};
  float camPitch = -15, camYaw = 0;
  float camFov = 60.0f;
  slim::FreeCamera camera({camPos[0], camPos[1], camPos[2]}, camPitch, camYaw, camFov);
  
  std::unique_ptr<slim::Shader> shader = slim::Shader::create("res/vertex.glsl", "res/fragment.glsl");
  shader->bind();
  shader->setMat4("uView", camera.getView());
  shader->setMat4("uProjection", camera.getProjection());

  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

  bool vsync = false;
  bool wireframes = false;

  slim::Time::init();
  while (!window->shouldClose())
  {
    slim::Time::start();

    shader->setMat4("uView", camera.getView());
    shader->setMat4("uProjection", camera.getProjection());
    cubemap->bind();
    vao->bind();

    glm::vec3 camPosVec = camera.getPosition();
    camPos[0] = camPosVec.x;
    camPos[1] = camPosVec.y;
    camPos[2] = camPosVec.z;
    camPitch = camera.getPitch();
    camYaw = camera.getYaw();
    camFov = camera.getFov();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (int i = 0; i < cubeCount; i++)
    {
      glm::mat4 model(1.0f);
      model = glm::translate(model, cubePositions[i]);
      shader->setMat4("uModel", model);

      glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Settings");

    if (ImGui::Checkbox("VSync", &vsync))
      window->setVsync(vsync);

    if (ImGui::Checkbox("Wireframes", &wireframes))
      glPolygonMode(GL_FRONT_AND_BACK, wireframes ? GL_LINE : GL_FILL);

    ImGui::Text("Camera");
    if (ImGui::SliderFloat3("Position", camPos, -10.0f, 10.0f))
      camera.setPosition({camPos[0], camPos[1], camPos[2]});

    if (ImGui::SliderFloat("Pitch", &camPitch, -79.0f, 79.0f))
      camera.setPitch(camPitch);

    if (ImGui::SliderFloat("Yaw", &camYaw, -179.0f, 179.0f))
      camera.setYaw(camYaw);

    if (ImGui::SliderFloat("FOV", &camFov, 20.0f, 90.0f))
      camera.setFov(camFov);

    ImGui::End();

    ImGui::ShowMetricsWindow();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    window->update();
    slim::Time::end();
  }

  return 0;
}*/