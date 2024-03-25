#include "sandbox_scene.hpp"

#include <glad/gl.h>
#include <imgui.h>

auto SandboxScene::attach() noexcept -> void {
  GLuint vbo = 0;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  // NOLINTNEXTLINE
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_), vertices_, GL_STATIC_DRAW);

  glGenVertexArrays(1, &vao_);
  glBindVertexArray(vao_);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

  const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource_, nullptr);
  glCompileShader(vertexShader);

  const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource_, nullptr);
  glCompileShader(fragmentShader);

  shader_ = glCreateProgram();
  glAttachShader(shader_, vertexShader);
  glAttachShader(shader_, fragmentShader);
  glLinkProgram(shader_);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

auto SandboxScene::update() noexcept -> void {
  glUseProgram(shader_);
  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

auto SandboxScene::uiDraw() noexcept -> void { ImGui::ShowMetricsWindow(); }

auto SandboxScene::detach() noexcept -> void {}
