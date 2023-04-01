#include "core/window.h"
#include "core/time.h"
#include "rendering/shader.h"
#include "rendering/vertex_buffer.h"
#include "rendering/vertex_attribute.h"
#include "rendering/vertex_array.h"
#include "rendering/index_buffer.h"
#include "rendering/texture2d.h"
#include "rendering/cubemap.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/gl.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <stb_image.h>
#include <memory>

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

/*int main()
{
  std::unique_ptr<slim::Window> window = slim::Window::create();

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGui::StyleColorsDark();

  ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)window->getNative(), true);
  ImGui_ImplOpenGL3_Init("#version 410");

  std::unique_ptr<slim::Shader> shader = slim::Shader::create("res/vertex.glsl", "res/fragment.glsl");

  float vertices[] = {
    -0.5, -0.5, -0.5,    0.0, 0.0, 0.0, // Back Bottom Left
     0.5, -0.5, -0.5,    0.0, 1.0, 0.0, // Back Bottom Right
     0.5,  0.5, -0.5,    0.0, 1.0, 1.0, // Back Top Right
    -0.5,  0.5, -0.5,    0.0, 0.0, 1.0, // Back Top Left
    -0.5, -0.5,  0.5,    1.0, 0.0, 0.0, // Front Bottom Left
     0.5, -0.5,  0.5,    1.0, 1.0, 0.0, // Front Bottom Right
     0.5,  0.5,  0.5,    1.0, 1.0, 1.0, // Front Top Right
    -0.5,  0.5,  0.5,    1.0, 0.0, 1.0, // Front Top Left
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

  // Matrices
  glm::mat4 model(1.0f);
  model = glm::rotate(model, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));

  glm::mat4 view(1.0f);
  view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

  glm::vec2 dimensions = window->getDimensions();
  glm::mat4 projection = glm::perspective(glm::radians(65.0f), dimensions.x / dimensions.y, 0.1f, 100.0f);
  
  shader->bind();
  shader->setMat4("uModel", model);
  shader->setMat4("uView", view);
  shader->setMat4("uProjection", projection);

  // Drawing
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // ImGui
  bool vsync = false;
  bool wireframes = true;
  float fov = 65.0f;
  float rotationSpeed = 0.0000005f;

  while (!window->shouldClose())
  {
    model = glm::rotate(model, glm::radians(0.25f) * slim::Time::deltaTime * rotationSpeed, glm::vec3(0.0f, 1.0f, 0.0f));
    shader->setMat4("uModel", model);

    cubemap->bind();
    shader->bind();
    vao->bind();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Settings");
    if (ImGui::Checkbox("VSync", &vsync))
      window->setVsync(vsync);

    if (ImGui::Checkbox("Wireframes", &wireframes))
      wireframes ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    ImGui::Text("Camera");
    if (ImGui::SliderFloat("FOV", &fov, 20, 90))
    {
      projection = glm::perspective(glm::radians(fov), dimensions.x / dimensions.y, 0.1f, 100.0f);
      shader->setMat4("uProjection", projection);
    }

    ImGui::Text("Cube");
    ImGui::SliderFloat("Rotation Speed", &rotationSpeed, 0.0000001f, 0.00001f, "%.7f");
    ImGui::End();

    ImGui::ShowMetricsWindow();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());    

    window->update();
    slim::Time::update();
  }

  return 0;
}*/