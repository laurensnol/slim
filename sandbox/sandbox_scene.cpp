#include "sandbox_scene.hpp"

// IWYU pragma: no_include <string>
// IWYU pragma: no_include "glm/detail/qualifier.hpp"
// IWYU pragma: no_include "glm/detail/type_vec2.inl"

#include <glad/gl.h>
#include <imgui.h>
#include <imgui_internal.h>

#include <cassert>
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

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
#endif

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                        // cppcheck-suppress cstyleCast
                        (void*)(3 * sizeof(GLfloat)));  // NOLINT

#if defined(__clang__)
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

  // NOLINTEND

  glGenBuffers(1, &ebo_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
  // NOLINTNEXTLINE
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_), indices_,
               GL_STATIC_DRAW);

  glGenFramebuffers(1, &fbo_);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo_);

  glGenTextures(1, &texture_);
  glBindTexture(GL_TEXTURE_2D, texture_);
  // NOLINTNEXTLINE
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1920, 1080, 0, GL_RGB,
               GL_UNSIGNED_BYTE, nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         texture_, 0);

  glGenRenderbuffers(1, &rbo_);
  glBindRenderbuffer(GL_RENDERBUFFER, rbo_);
  // NOLINTNEXTLINE
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1920, 1080);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                            GL_RENDERBUFFER, rbo_);

  assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glBindTexture(GL_TEXTURE_2D, 0);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

auto SandboxScene::update() noexcept -> void {
  glBindFramebuffer(GL_FRAMEBUFFER, fbo_);

  if (isShowingWireframes_) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  } else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }

  shader_->bind();
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);  // NOLINT
  shader_->unbind();
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

auto SandboxScene::uiDraw() noexcept -> void {
  initDockspace();
  showMetricsWindow();
  showPropertiesWindow();
  showViewportWindow();
}

auto SandboxScene::detach() noexcept -> void {
  glDeleteFramebuffers(1, &fbo_);
  glDeleteTextures(1, &texture_);
  glDeleteRenderbuffers(1, &rbo_);
}

auto SandboxScene::initDockspace() noexcept -> void {
  const ImGuiID dockspaceId = ImGui::GetID(dockspaceName_);

  if (ImGui::DockBuilderGetNode(dockspaceId) == nullptr) {
    ImGui::DockBuilderRemoveNode(dockspaceId);
    ImGui::DockBuilderAddNode(dockspaceId);

    ImGuiID viewportId = dockspaceId;
    ImGuiID propertiesId = ImGui::DockBuilderSplitNode(
        viewportId, ImGuiDir_Left, 0.2F, nullptr, &viewportId);  // NOLINT
    const ImGuiID metricsId = ImGui::DockBuilderSplitNode(
        propertiesId, ImGuiDir_Down, 0.35F, nullptr, &propertiesId);  // NOLINT

    ImGui::DockBuilderDockWindow("Viewport", viewportId);
    ImGui::DockBuilderDockWindow("Properties", propertiesId);
    ImGui::DockBuilderDockWindow("Dear ImGui Metrics/Debugger", metricsId);
    ImGui::DockBuilderFinish(dockspaceId);
  }

  const ImGuiViewport* viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(viewport->Pos);
  ImGui::SetNextWindowSize(viewport->Size);
  ImGui::SetNextWindowViewport(viewport->ID);

  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0F);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0F);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0F, 0.0F));
  ImGui::Begin("Sandbox", &isUiShown_, sandboxWindowFlags_);
  ImGui::PopStyleVar(3);
  ImGui::DockSpace(dockspaceId, ImVec2(0.0F, 0.0F), 0);
  ImGui::BeginMenuBar();
  ImGui::Text("Sandbox");  // NOLINT
  ImGui::EndMenuBar();
  ImGui::End();
}

auto SandboxScene::showMetricsWindow() noexcept -> void {
  ImGui::ShowMetricsWindow();
}

auto SandboxScene::showPropertiesWindow() noexcept -> void {
  ImGui::Begin("Properties");
  ImGui::Checkbox("Wireframes", &isShowingWireframes_);
  ImGui::SeparatorText("Viewport");
  // NOLINTNEXTLINE
  ImGui::Text("Dimensions: %ix%i", viewportWidth_, viewportHeight_);
  ImGui::End();
}

auto SandboxScene::showViewportWindow() noexcept -> void {
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0F, 0.0F));
  ImGui::Begin("Viewport");
  ImGui::BeginChild("Scene");

  const ImVec2 size = ImGui::GetContentRegionAvail();
  viewportWidth_ = static_cast<GLint>(size.x);
  viewportHeight_ = static_cast<GLint>(size.y);

  // Rescale Framebuffer
  glBindTexture(GL_TEXTURE_2D, texture_);
  // NOLINTNEXTLINE
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, viewportWidth_, viewportHeight_, 0,
               GL_RGB, GL_UNSIGNED_BYTE, nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         texture_, 0);

  glGenRenderbuffers(1, &rbo_);
  glBindRenderbuffer(GL_RENDERBUFFER, rbo_);
  // NOLINTNEXTLINE
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, viewportWidth_,
                        viewportHeight_);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                            GL_RENDERBUFFER, rbo_);

  slim::Renderer::setViewport({0, 0}, {viewportWidth_, viewportHeight_});

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wold-style-cast"
#pragma clang diagnostic ignored "-Wint-to-void-pointer-cast"
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
#endif

  // cppcheck-suppress-begin cstyleCast
  // NOLINTNEXTLINE
  ImGui::Image((ImTextureID)texture_, size, ImVec2(0, 1), ImVec2(1, 0));
  // cppcheck-suppress-end cstyleCast

#if defined(__clang__)
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

  ImGui::EndChild();
  ImGui::End();
  ImGui::PopStyleVar();
}
