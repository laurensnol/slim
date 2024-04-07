#ifndef SLIM_SANDBOX_SANDBOX_SCENE_HPP_
#define SLIM_SANDBOX_SANDBOX_SCENE_HPP_

#include <glad/gl.h>
#include <imgui.h>

#include <cstdint>
#include <memory>
#include <slim/slim.hpp>

class SandboxScene : public slim::Scene {
public:
  auto attach() noexcept -> void override;
  auto update() noexcept -> void override;
  auto uiDraw() noexcept -> void override;
  auto detach() noexcept -> void override;

private:
  // clang-format off
  // NOLINTNEXTLINE
  constexpr static const GLfloat vertices_[] = {
    // NE, white
     0.5F,  0.5F, 0.0F, 1.0F, 1.0F, 1.0F,
    // SE, yellow
     0.5F, -0.5F, 0.0F, 1.0F, 1.0F, 0.0F,
    // SW, red
    -0.5F, -0.5F, 0.0F, 1.0F, 0.0F, 0.0F,
    // NW, Magenta
    -0.5F,  0.5F, 0.0F, 1.0F, 0.0F, 1.0F
  };

  // NOLINTNEXTLINE
  constexpr static const GLuint indices_[] = {
    0, 1, 3,
    1, 2, 3
  };
  // clang-format on

  std::shared_ptr<slim::Shader> shader_;
  GLuint ebo_ = 0;
  GLuint fbo_ = 0;
  GLuint texture_ = 0;
  GLuint rbo_ = 0;

  inline static constexpr const char* dockspaceName_ = "SandboxDockspace";
  inline static bool isUiShown_ = true;
  static constexpr const ImGuiWindowFlags sandboxWindowFlags_ =
      ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking |
      ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
      ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
      ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

  bool isShowingWireframes_ = false;
  int32_t viewportWidth_ = 0;
  int32_t viewportHeight_ = 0;

  // cppcheck-suppress-begin unusedPrivateFunction
  static auto initDockspace() noexcept -> void;
  static auto showMetricsWindow() noexcept -> void;
  auto showPropertiesWindow() noexcept -> void;
  auto showViewportWindow() noexcept -> void;
  // cppcheck-suppress-end unusedPrivateFunction
};

#endif  // SLIM_SANDBOX_SANDBOX_SCENE_HPP_
