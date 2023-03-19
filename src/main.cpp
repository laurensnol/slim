#include "core/window.h"
#include "rendering/shader.h"

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
     0.0,  0.5, 0.0   // N
  };

  GLuint vao, vbo;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  while (!window->shouldClose())
  {
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();
    ImGui::ShowMetricsWindow();
    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    shader->bind();
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    window->update();
  }

  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);

  return 0;
}
