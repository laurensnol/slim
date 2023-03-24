#include "core/window.h"
#include "rendering/shader.h"
#include "rendering/vertex_buffer.h"
#include "rendering/vertex_attribute.h"
#include "rendering/vertex_array.h"
#include "rendering/index_buffer.h"

#include <glm/glm.hpp>
#include <glad/gl.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <memory>

int main()
{
  std::unique_ptr<slim::Window> window = slim::Window::create();

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGui::StyleColorsDark();

  ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)window->getNative(), true);
  ImGui_ImplOpenGL3_Init("#version 410");

  std::unique_ptr<slim::Shader> shader = slim::Shader::create("res/vertex.glsl", "res/fragment.glsl");

  float vertices[] = {
    -0.5, -0.5, 0.0,  // SW
     0.5, -0.5, 0.0,  // SE
     0.5,  0.5, 0.0,  // NE
    -0.5,  0.5, 0.0,  // NW
  };

  unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
  };

  std::shared_ptr<slim::VertexBuffer> vbo = slim::VertexBuffer::create(vertices, sizeof(vertices));
  
  slim::VertexAttribute attr = slim::VertexAttribute(0, slim::VertexAttributeBaseType::Float3, false);
  vbo->addAttribute(attr);

  std::shared_ptr<slim::VertexArray> vao = slim::VertexArray::create();
  vao->addVertexBuffer(vbo);

  std::shared_ptr<slim::IndexBuffer> ibo = slim::IndexBuffer::create(indices, 6);
  vao->setIndexBuffer(ibo);

  uint32_t indicesCount = ibo->count();
  float color[3] = {0.0, 1.0, 0.0};

  while (!window->shouldClose())
  {
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    shader->bind();
    vao->bind();
    glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);

    ImGui::ShowMetricsWindow();

    ImGui::Begin("Rectangle");
    ImGui::SliderFloat3("Color", color, 0, 1.0);
    glm::vec4 colorVec{color[0], color[1], color[2], 1.0};
    shader->setFloat4("color", colorVec);
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    window->update();
  }

  return 0;
}
