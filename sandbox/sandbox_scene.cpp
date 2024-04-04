#include "sandbox_scene.hpp"

// IWYU pragma: no_include <string>

#include <glad/gl.h>
#include <imgui.h>

#include <filesystem>
#include <slim/slim.hpp>

auto SandboxScene::attach() noexcept -> void {
  auto dir = std::filesystem::current_path().append("sandbox");
  auto vertexShaderPath = dir / "vertex.glsl";
  auto fragmentShaderPath = dir / "fragment.glsl";
  shader_ = slim::Shader::create(vertexShaderPath.string(),
                                 fragmentShaderPath.string());

  GLuint vbo = 0;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  // NOLINTNEXTLINE
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_), vertices_, GL_STATIC_DRAW);

  GLuint vao = 0;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  // NOLINTBEGIN
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), nullptr);

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wold-style-cast"
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                        // cppcheck-suppress cstyleCast
                        (void*)(3 * sizeof(GLfloat)));  // NOLINT
#pragma clang diagnostic pop
  // NOLINTEND

  glGenBuffers(1, &ebo_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
  // NOLINTNEXTLINE
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_), indices_,
               GL_STATIC_DRAW);
}

auto SandboxScene::update() noexcept -> void {
  shader_->bind();
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);  // NOLINT
}

auto SandboxScene::uiDraw() noexcept -> void { ImGui::ShowMetricsWindow(); }

auto SandboxScene::detach() noexcept -> void {}
